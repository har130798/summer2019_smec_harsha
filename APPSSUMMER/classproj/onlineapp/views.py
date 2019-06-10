from django.shortcuts import render
from django.http import HttpResponse
from .models import *

# Create your views here.


def hello(request):
    return HttpResponse(request.headers['foo'])

def get_my_college(request, acronym):
    try:
        return HttpResponse(College.objects.filter(acronym=acronym).values('name')[0]['name'])
    except Exception:
        return HttpResponse('College not available')

def get_all_colleges(request):
    try:
        colls = College.objects.values('name', 'acronym', 'id').all()
        return render(request, 'colleges.html', {'colleges' : colls})
    except Exception as e:
        print(e)

        return HttpResponse('Some error occurred', status=400)

def get_college_student_info(request, coll_id):
    try:

        students = MockTest1.objects.values('total', 'student__id', 'student__name').filter(student__college__id=coll_id)
        if len(students) == 0:
            raise Exception('No such college')
        return render(request, 'collstuinfo.html', {'students' : students})
    except Exception as e:
        print(e)
        return HttpResponse('Some error occurred or No such college exists', status=400)