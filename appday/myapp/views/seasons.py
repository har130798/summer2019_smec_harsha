from rest_framework.views import APIView
from rest_framework.response import Response
from myapp.serializers import *
from rest_framework.authentication import BasicAuthentication, TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from django.contrib.auth.models import User


class SeasonsView(APIView):
    def get(self, request, *args, **kwargs):
        seasons = set([x['season'] for x in Match.objects.values('season')])
        if kwargs:
            data = Match.objects.filter(**kwargs)
            season_data = SeasonSerializer(data, many=True).data
            return Response(season_data)

        return Response(data = {'seasons': sorted(list(seasons), reverse=True)})

class MatchView(APIView):
    def get(self, *args, **kwargs):
        if 'id' in kwargs.keys():
            match = Match.objects.get(id=kwargs.get('id'))
            match_data = MatchSerializer(match).data
            deliveries = Delivery.objects.filter(match_id=match.id)
            delivery_data = DeliverySerializer(deliveries, many=True).data
            data = {
                'match_data': match_data,
                'deliveries_1': sorted(filter(lambda delivery: delivery['inning'] == 1, delivery_data), key=lambda x:( x['over'], x['ball'] )),
                'deliveries_2': sorted(filter(lambda delivery: delivery['inning'] == 2, delivery_data), key=lambda x:( x['over'], x['ball'] )),
            }
            stats = get_match_stats(data)
            data['stats'] = stats

            return Response(data)


def get_match_stats(data):
    batsmen_1 = set([x['batsman'] for x in data['deliveries_1']])
    batsmen_2 = set([x['batsman'] for x in data['deliveries_2']])
    bowlers_1 = set([x['bowler'] for x in data['deliveries_2']])
    bowlers_2 = set([x['bowler'] for x in data['deliveries_1']])

    scores_1 = dict([(x, 0) for x in batsmen_1])
    scores_2 = dict([(x, 0) for x in batsmen_2])

    wickets_1 = dict([(x, 0) for x in bowlers_1])
    wickets_2 = dict([(x, 0) for x in bowlers_2])

    extras_1 = 0
    extras_2 = 0

    for ball in data['deliveries_1']:
        scores_1[ball['batsman']] += ball['batsman_runs']
        if len(ball['player_dismissed']) != 0:
            wickets_2[ball['bowler']] += 1
        extras_2 += ball['extra_runs']


    for ball in data['deliveries_2']:
        scores_2[ball['batsman']] += ball['batsman_runs']
        if len(ball['player_dismissed']) != 0:
            wickets_1[ball['bowler']] += 1
        extras_1 += ball['extra_runs']

    return {
        'top3_1': sorted([(x, scores_1[x]) for x in scores_1.keys()], key=lambda x: -x[1])[:3],
        'top3_2': sorted([(x, scores_2[x]) for x in scores_2.keys()], key=lambda x: -x[1])[:3],
        'top3b_1': sorted([(x, wickets_1[x]) for x in wickets_1.keys()], key=lambda x: -x[1])[:3],
        'top3b_2': sorted([(x, wickets_2[x]) for x in wickets_2.keys()], key=lambda x: -x[1])[:3],
        'extras_1': extras_1,
        'extras_2': extras_2
    }

class PointsView(APIView):
    def get(self, request, *args, **kwargs):
        matches = Match.objects.filter(**kwargs)
        table = create_points_table(matches)
        return Response(sorted(table, key= lambda x:(-x[3], x[0])))


def create_points_table(input_data):
    teams = set([x.team1 for x in input_data])

    data = dict([(x, [0, 0, 0, 0]) for x in teams])
    for row in input_data:
        if len(row.winner) != 0:
            data[row.winner][1] += 1
            data[row.winner][3] += 2
            loser = row.team1 if row.team2 == row.winner else row.team2
            data[loser][0] += 1
            continue
        data[row.team1][2] += 1
        data[row.team2][2] += 1
        data[row.team1][3] += 1
        data[row.team2][3] += 1

    [data[x].append(x) for x in data]

    return data.values()

class SignUpView(APIView):
    def post(self, request, *args, **kwargs):
        serializer = UserSerializer(data=request.data)

        if serializer.is_valid():
            user = User.objects.create_user(**request.data)
            user.save()
            return Response(UserSerializer(user).data)
        return Response(serializer.errors, status=400)

class UserView(APIView):

    authentication_classes = (BasicAuthentication, TokenAuthentication)
    permission_classes = (IsAuthenticated,)

    def get(self, request, *args, **kwargs):
        user = User.objects.get_by_natural_key(request.user.username)
        serializer = UserSerializer(user)

        return Response(serializer.data)

teams = {
    'srh': 'Sunrisers Hyderabad',
    'csk': 'Chennai Super Kings',
    'mi': 'Mumbai Indians',
    'dd': 'Delhi Daredevils',
    'dc': 'Delhi Capitals',
    'rr': 'Rajasthan Royals',
    'rps': 'Rising Pune Supergiants',
    'ktk': 'Kochi Tuskers Kerela',
    'rcb': 'Royal Challengers Bangalore',
    'kkr': 'Kolkata Knight Riders',
    'kxip': 'Kings XI Punjab',
    'dec': 'Deccan Chargers'
    }

class TeamView(APIView):
    def get(self, request, *args, **kwargs):
        teamname = teams[kwargs.get('team')]

        matches_1 = Match.objects.filter(team1=teamname)
        matches_2 = Match.objects.filter(team2=teamname)

        serializer_1 = MatchSerializer(matches_1, many=True)
        serializer_2 = MatchSerializer(matches_2, many=True)

        return Response(serializer_1.data+serializer_2.data)