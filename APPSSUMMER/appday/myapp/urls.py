from django.urls import path
from rest_framework.authtoken.views import obtain_auth_token
from myapp.views import *

urlpatterns = [
    path('api/v1/signup', SignUpView.as_view(), name='signup'),
    path('api/v1/token', obtain_auth_token, name='signup'),
    path('api/v1/me', UserView.as_view(), name='signup'),
    path('api/v1/seasons', SeasonsView.as_view(), name='signup'),
    path('api/v1/seasons/<int:season>', SeasonsView.as_view(), name='signup'),
    path('api/v1/matches/<int:id>', MatchView.as_view(), name='signup'),
    path('api/v1/pointstable/<int:season>', PointsView.as_view(), name='signup'),
    path('api/v1/teams/<str:team>', TeamView.as_view(), name='signup'),
]