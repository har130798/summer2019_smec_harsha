from django.urls import path

from . import views

urlpatterns = [
    path('hello/', views.hello),
    path('get_my_college/<str:acronym>', views.get_my_college),
    path('get_all_colleges/', views.get_all_colleges),
    path('college_student_info/<int:coll_id>', views.get_college_student_info),
]