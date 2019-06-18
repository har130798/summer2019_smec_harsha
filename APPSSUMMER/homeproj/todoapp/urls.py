from django.urls import path
from todoapp.views import *
from rest_framework.authtoken.views import obtain_auth_token

urlpatterns = [
    path('login/', LoginView.as_view(), name='login'),
    path('signup/', SignupView.as_view(), name='signup'),
    path('logout/', logout_user, name='logout'),
    path('todolist/', TodolistView.as_view(), name='todolist'),
    path('todolist/add', TodolistFormView.as_view(), name='addtodolist'),
    path('todolist/edit/<int:id>', TodolistFormView.as_view(), name='edittodolist'),
    path('todolist/delete/<int:id>', TodolistFormView.as_view(), name='deletetodolist'),
    path('todolist/<int:todolist_id>', TodoitemsView.as_view(), name='todoitems'),
    path('todolist/<int:todolist_id>/add', TodoitemsFormView.as_view(), name='addtodoitems'),
    path('todolist/<int:todolist_id>/edit/<int:id>', TodoitemsFormView.as_view(), name='edittodoitem'),
    path('todolist/<int:todolist_id>/delete/<int:id>', TodoitemsFormView.as_view(), name='deletetodoitem'),
    path('api/v1/todolist', TodolistRestView.as_view(), name='rest_todolists'),
    path('api/v1/todolist/<int:id>', TodolistRestView.as_view(), name='rest_todolist'),
    path('api/v1/todolist/<int:todolist_id>/todoitem', TodoitemRestView.as_view(), name='rest_todoitems'),
    path('api/v1/todolist/<int:todolist_id>/todoitem/<int:id>', TodoitemRestView.as_view(), name='rest_todoitem'),
    path('api/v1/token', obtain_auth_token, name='rest_token_grant'),
]