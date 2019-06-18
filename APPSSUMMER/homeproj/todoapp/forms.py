from django.forms import ModelForm, TextInput, Form, CharField, PasswordInput, DateTimeInput
from .models import Todolist, Todoitem


class TodolistForm(ModelForm):

    class Meta:
        model = Todolist
        exclude = ['id', 'created', 'user']

        widgets = {
            'name' : TextInput(attrs={'class' : '', 'placeholder' : 'Enter name'}),
        }

class TodoitemForm(ModelForm):
        class Meta:
            model = Todoitem
            exclude = ['id', 'todolist', 'completed']
            fields = ['description', 'due_date']
            widgets = {
                'description': TextInput(attrs={'class': '', 'placeholder': 'Enter description'}),
                'due_date': DateTimeInput(format=['%d/%m/%Y %H:%M'], attrs={
                    'class': '',
                    'placeholder': 'enter date'
                },),
            }

class LoginForm(Form):
    username = CharField(
        required=True,
        max_length=50,
        min_length=3,
        widget=TextInput(
            attrs={
                'placeholder': 'Enter username',
            }
        )
    )

    password = CharField(
        required=True,
        max_length=50,
        min_length=1,
        widget=PasswordInput(
            attrs={
                'placeholder': 'Enter password',
            }
        )
    )

class SignupForm(Form):
    firstname = CharField(
        widget=TextInput(
            attrs={
                'placeholder': 'Enter first name',
            }
        )
    )

    lastname = CharField(
        widget=TextInput(
            attrs={
                'placeholder': 'Enter last name',
            }
        )
    )

    username = CharField(
        widget=TextInput(
            attrs={
                'placeholder': 'Enter username',
            }
        )
    )

    password = CharField(
        widget=PasswordInput(
            attrs={
                'placeholder': 'Enter password',
            }
        )
    )