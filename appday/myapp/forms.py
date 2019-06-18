from django.forms import ModelForm, TextInput, Form, CharField, PasswordInput

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