from django.views import View
from django.shortcuts import render, redirect
from todoapp.forms import *
from django.contrib.auth.models import User
from django.http import HttpResponse
from django.urls import resolve

class TodolistView(View):
    template_name = 'todolist.html'
    def get(self, request,  *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')

        todolists = Todolist.objects.filter(user_id=request.user.id)

        return render(
            request,
            template_name=self.template_name,
            context= {
                'lists': todolists,
                'user': request.user
            }
        )

class TodoitemsView(View):
    template_name = 'todoitems.html'
    def get(self, request, *args, **kwargs):
        if not kwargs:
            return HttpResponse(status=400)

        todoitems = Todoitem.objects.filter(**kwargs)

        return render(
            request,
            self.template_name,
            context= {
                'items': todoitems,
                'todolist' : Todolist.objects.get(id=kwargs.get('todolist_id')),
                'user': request.user
            }
        )

class TodolistFormView(View):
    template_name = 'todolistform.html'

    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')

        #TODO add error handling
        if resolve(request.path_info).url_name == 'edittodolist':
            instance = Todolist.objects.get(**kwargs)
            form = TodolistForm(instance=instance)
        elif resolve(request.path_info).url_name == 'deletetodolist':
            instance = Todolist.objects.get(**kwargs)
            instance.delete()
            return redirect('todolist')
        else:
            form = TodolistForm()

        return render(
            request,
            template_name=self.template_name,
            context= {
                'form': form,
                'user': request.user.is_authenticated
            }
        )

    def post(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')

        if resolve(request.path_info).url_name == 'edittodolist':
            instance = Todolist.objects.get(**kwargs)
            form = TodolistForm(instance=instance, data=request.POST)
            if form.is_valid():
                form.save()
                return redirect('todolist')
        else:
            form = TodolistForm(data=request.POST)

        if form.is_valid():
            todolist = form.save(commit=False)
            todolist.user = User.objects.get_by_natural_key(request.user.username)
            todolist.save()
            return redirect('todolist')

        else:
            return render(
                request,
                self.template_name,
                {
                    'form': form,
                    'user': request.user.is_authenticated
                }
            )

class TodoitemsFormView(View):
    template_name = 'todoitemform.html'

    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')

        if resolve(request.path_info).url_name == 'edittodoitem':
            instance = Todoitem.objects.get(**kwargs)
            form = TodoitemForm(instance=instance)
        elif resolve(request.path_info).url_name == 'deletetodoitem':
            instance = Todoitem.objects.get(**kwargs)
            instance.delete()
            return redirect('todolist')
        else:
            form = TodoitemForm()

        return render(
            request,
            template_name=self.template_name,
            context= {
                'form': form,
                'user': request.user.is_authenticated
            }
        )

    def post(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')

        if resolve(request.path_info).url_name == 'edittodoitem':
            instance = Todoitem.objects.get(**kwargs)
            form = TodoitemForm(instance=instance, data=request.POST)

            if form.is_valid():
                form.save()
                return redirect('todolist')
            return render(
                request,
                self.template_name,
                {
                    'form': form,
                    'user': request.user.is_authenticated
                }
            )

        form = TodoitemForm(data=request.POST)

        if form.is_valid():
            todoitem = form.save(commit=False)
            todoitem.todolist = Todolist.objects.get(id=kwargs.get('todolist_id'))
            todoitem.save()
            return redirect('todolist')

        else:
            return render(
                request,
                self.template_name,
                {
                    'form': form,
                    'user': request.user.is_authenticated
                }
            )