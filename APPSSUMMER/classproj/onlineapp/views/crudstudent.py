from django.views import View
from django.shortcuts import render, redirect
from onlineapp.forms import *
from django.http import HttpResponse
from django.urls import resolve


class CrudStudentView(View):
    template_name = 'studentform.html'
    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')
        elif request.user.is_superuser == False:
            return redirect('colleges_html')
        stu, mock = None, None
        if kwargs:
            if resolve(request.path_info).url_name == 'student_edit':
                student = Student.objects.get(**kwargs)
                mock = Mocktest1Form(instance=MockTest1.objects.get(student_id=student.id))
                stu = StudentForm(instance=student)

            elif resolve(request.path_info).url_name == 'student_delete':
                student = Student.objects.get(**kwargs)
                student.delete()
                return redirect('colleges_html')
            else:
                stu = StudentForm()
                mock = Mocktest1Form()

        return render(
            request,
            template_name=self.template_name,
            context= {
                'student_form' : stu,
                'mocktest1_form': mock,
                'user': request.user
            }
        )


    def post(self, request, *args, **kwargs):
        if kwargs:
            if resolve(request.path_info).url_name == 'student_edit':
                student = Student.objects.get(**kwargs)
                stu = StudentForm(request.POST, instance=student)
                stu.save()

                mock = Mocktest1Form(request.POST, instance=MockTest1.objects.get(student_id=student.id))
                mocktest1 = mock.save(commit=False)
                mocktest1.total = sum([
                    mocktest1.problem1,
                    mocktest1.problem2,
                    mocktest1.problem3,
                    mocktest1.problem4,
                ])
                mocktest1.save()
                return redirect('colleges_html')

            else:
                college = College.objects.get(**kwargs)
                if request.method.upper() == 'POST':

                    student_form = StudentForm(request.POST)
                    mocktest1_form = Mocktest1Form(request.POST)

                    if student_form.is_valid() and mocktest1_form.is_valid():
                        student = student_form.save(commit=False)
                        student.college = college
                        student.save()

                        mocktest1 = mocktest1_form.save(commit=False)
                        mocktest1.student = student
                        mocktest1.total = sum([
                            mocktest1.problem1,
                            mocktest1.problem2,
                            mocktest1.problem3,
                            mocktest1.problem4,
                        ])
                        mocktest1.save()

                        return redirect('colleges_html')
                    else:
                        return render(
                            request,
                            template_name=self.template_name,
                            context={
                                  'student_form': student_form,
                                  'mocktest1_form': mocktest1_form,
                                  'user': request.user
                            }
                        )
                else:
                    return HttpResponse('Wrong method', status=404)
        else:
            return HttpResponse('Something went wrong', status=400)