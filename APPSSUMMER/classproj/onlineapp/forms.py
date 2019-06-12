from django.forms import ModelForm, TextInput, Form, CharField, PasswordInput
from .models import *


class CollegeForm(ModelForm):

    class Meta:
        model = College
        exclude = ['id']

        widgets = {
            'name' : TextInput(attrs={'class' : '', 'placeholder' : 'Enter name'}),
            'acronym' : TextInput(attrs={'class' : '', 'placeholder' : 'Enter acronym'}),
            'contact' : TextInput(attrs={'class' : '', 'placeholder' : 'Enter contact'}),
            'location' : TextInput(attrs={'class' : '', 'placeholder' : 'Enter contact'}),
        }

class StudentForm(ModelForm):
        class Meta:
            model = Student
            exclude = ['id', 'college']
            fields = ['name', 'email', 'dbname']
            widgets = {
                'name': TextInput(attrs={'class': '', 'placeholder': 'Enter name'}),
                'email': TextInput(attrs={'class': '', 'placeholder': 'Enter email'}),
                'dbname': TextInput(attrs={'class': '', 'placeholder': 'Enter dbname'})
            }

class Mocktest1Form(ModelForm):
    class Meta:
        model = MockTest1
        exclude = ['id', 'total', 'student']
        fields = ['problem1', 'problem2', 'problem3', 'problem4']
        widgets = {
            'problem1': TextInput(attrs={'class': '', 'placeholder': 'Enter problem1 marks'}),
            'problem2': TextInput(attrs={'class': '', 'placeholder': 'Enter problem2 marks'}),
            'problem3': TextInput(attrs={'class': '', 'placeholder': 'Enter problem3 marks'}),
            'problem4': TextInput(attrs={'class': '', 'placeholder': 'Enter problem4 marks'}),
        }

class LoginForm(Form):
    username = CharField(
        required=True,
        max_length=50,
        min_length=3,
        widget= TextInput(
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
        required=True,
        max_length=50,
        min_length=3,
        widget=TextInput(
            attrs={
                'placeholder': 'Enter first name',
            }
        )
    )

    lastname = CharField(
        required=True,
        max_length=50,
        min_length=3,
        widget=TextInput(
            attrs={
                'placeholder': 'Enter last name',
            }
        )
    )

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