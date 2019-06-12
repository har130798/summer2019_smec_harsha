from django.views import View
from django.shortcuts import render, redirect
from onlineapp.forms import *
from django.http import HttpResponse
from django.urls import resolve

class CrudCollegeView(View):
    template_name = 'collegeform.html'
    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')
        elif request.user.is_superuser == False:
            return redirect('colleges_html')
        form = CollegeForm()

        if kwargs:
            college = College.objects.get(**kwargs)
            form = CollegeForm(instance=college)
            if resolve(request.path_info).url_name == 'college_delete':
                college.delete()
                return redirect('colleges_html')

        return render(
            request,
            template_name=self.template_name,
            context= {
                'form' : form,
                'user': request.user
            }
        )


    def post(self, request, *args, **kwargs):
        if kwargs:
            c = College.objects.get(**kwargs)

            if resolve(request.path_info).url_name == 'college_edit':
                form = CollegeForm(request.POST, instance=c)
                if form.is_valid():
                    form.save()
                    return redirect('colleges_html')
                else:
                    return render(request, template_name=self.template_name, context={'form': form, 'user': request.user})

        if request.method.upper() == 'POST':
            form = CollegeForm(request.POST)
            if form.is_valid():
                form.save()
                return redirect('colleges_html')
            else:
                return render(request, template_name=self.template_name, context={'form' : form, 'user': request.user})
        else:
            return HttpResponse('Wrong method', status=404)