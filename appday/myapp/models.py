from django.db.models import *

# Create your models here.
class Match(Model):
    id = IntegerField(primary_key=True)
    season = IntegerField(blank=True, null=True)
    city = CharField(max_length=255, blank=True, null=True)
    date = DateField(blank=True, null=True)
    team1 = CharField(max_length=255, blank=True, null=True)
    team2 = CharField(max_length=255, blank=True, null=True)
    toss_decision = CharField(max_length=255, blank=True, null=True)
    toss_winner = CharField(max_length=255, blank=True, null=True)
    result = CharField(max_length=255, blank=True, null=True)
    dl_applied = IntegerField(blank=True, null=True)
    winner = CharField(max_length=255, blank=True, null=True)
    win_by_runs = IntegerField(blank=True, null=True)
    win_by_wickets = IntegerField(blank=True, null=True)
    player_of_match = CharField(max_length=255, blank=True, null=True)
    venue = CharField(max_length=255, blank=True, null=True)
    umpire1 = CharField(max_length=255, blank=True, null=True)
    umpire2 = CharField(max_length=255, blank=True, null=True)
    umpire3 = CharField(max_length=255, blank=True, null=True)


class Delivery(Model):
    match = ForeignKey(Match, on_delete=CASCADE)
    inning = IntegerField()
    batting_team = CharField(max_length=255, blank=True, null=True)
    bowling_team = CharField(max_length=255, blank=True, null=True)
    over = IntegerField()
    ball = IntegerField()
    batsman = CharField(max_length=255, blank=True, null=True)
    bowler = CharField(max_length=255, blank=True, null=True)
    non_striker = CharField(max_length=255, blank=True, null=True)
    is_super_over = IntegerField()
    wide_runs = IntegerField()
    legbye_runs = IntegerField()
    bye_runs = IntegerField()
    noball_runs = IntegerField()
    penalty_runs = IntegerField()
    batsman_runs = IntegerField()
    extra_runs = IntegerField()
    total_runs = IntegerField()
    player_dismissed = CharField(max_length=255, blank=True, null=True)
    dismissal_kind = CharField(max_length=255, blank=True, null=True)
    fielder = CharField(max_length=255, blank=True, null=True)




