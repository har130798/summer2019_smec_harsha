from rest_framework.serializers import ModelSerializer
from todoapp.models import *

class TodolistSerializer(ModelSerializer):
    class Meta:
        model = Todolist
        fields = ('id', 'name', 'user', 'created')

class TodoitemSerializer(ModelSerializer):
    class Meta:
        model = Todoitem
        fields = ('id', 'description', 'due_date', 'todolist')