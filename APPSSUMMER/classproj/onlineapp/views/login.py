from django.views import View
from django.shortcuts import render, redirect
from onlineapp.forms import *
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User

class LoginView(View):
    template_name = 'login.html'
    def get(self, request,  *args, **kwargs):
        form = LoginForm()

        return render(
            request,
            template_name=self.template_name,
            context= {
                'form': form
            }
        )

    def post(self, request, *args, **kwargs):
        form = LoginForm(request.POST)

        if form.is_valid():
            user = authenticate(request, username=form.cleaned_data['username'],password=form.cleaned_data['password'])
            if user is not None:
                login(
                    request,
                    user=user
                )

                return redirect('colleges_html')
            else:
                return redirect('login')
        return redirect('login')


class SignupView(View):
    template_name = 'signup.html'
    def get(self, request, *args, **kwargs):
        form = SignupForm()

        return render(
            request,
            template_name=self.template_name,
            context= {
                'form' : form
            }
        )

    def post(self, request, *args, **kwargs):
        userform = SignupForm(request.POST)

        if userform.is_valid():
            User.objects.create_user(
                username=userform.cleaned_data['username'],
                first_name=userform.cleaned_data['firstname'],
                last_name=userform.cleaned_data['lastname'],
                password=userform.cleaned_data['password'],
            )

            return redirect('login')
        return redirect('signup')

def logout_user(request):
    logout(request)
    return redirect('login')