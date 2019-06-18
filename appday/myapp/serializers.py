from rest_framework.serializers import ModelSerializer
from django.contrib.auth.models import User
from myapp.models import Match, Delivery

class UserSerializer(ModelSerializer):
    class Meta:
        model = User
        fields = ('first_name', 'last_name', 'username', 'password', 'id')

class SeasonSerializer(ModelSerializer):
    class Meta:
        model = Match
        fields = ('id', 'date', 'team1', 'team2', 'venue', 'toss_winner', 'toss_decision', 'player_of_match', 'result', 'winner')

class DeliverySerializer(ModelSerializer):
    class Meta:
        model = Delivery
        fields = ('inning', 'batting_team', 'bowling_team', 'over', 'ball', 'batsman', 'non_striker', 'bowler',
                  'total_runs', 'player_dismissed', 'batsman_runs', 'extra_runs', 'dismissal_kind', 'fielder')

class MatchSerializer(ModelSerializer):
    class Meta:
        model = Match
        fields = ('id', 'date', 'team1', 'team2', 'venue', 'toss_winner', 'toss_decision', 'player_of_match', 'result', 'winner',
                  'win_by_runs', 'win_by_wickets', 'player_of_match')