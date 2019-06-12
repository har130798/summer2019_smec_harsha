from django.views import View
from django.shortcuts import render, redirect
from onlineapp.models import College, MockTest1
from django.http import HttpResponse

class CollegeView(View):
    template_name = 'colleges.html'

    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated == False:
            return redirect('login')
        try:

            if kwargs:
                college = College.objects.get(**kwargs)
                students = MockTest1.objects.values('total', 'student__id', 'student__name').filter(
                    student__college__id=college.id)

                if len(students) == 0:
                    return HttpResponse('<h1>No students exist</h1>', status=404)

                return render(request, template_name="collstuinfo.html", context={'students': students, 'college': college, 'user': request.user})

            colleges = College.objects.all()
            return render(request, template_name=self.template_name, context={'colleges' : colleges, 'user': request.user})

        except Exception as e:
            print(e)
        return HttpResponse('<h1>Some error occurred. Try again later</h1>', status=400)