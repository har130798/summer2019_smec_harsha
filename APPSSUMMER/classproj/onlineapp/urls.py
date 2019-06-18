from django.urls import path

from . import views
from onlineapp.views import *

urlpatterns = [
    path('colleges/', CollegeView.as_view(), name='colleges_html'),
    path('colleges/<int:id>', CollegeView.as_view(), name='collstuinfo_html'),
    path('colleges/<str:acronym>', CollegeView.as_view(), name='collstuinfo_html'),
    path('college/add', CrudCollegeView.as_view(), name='collegeform_html'),
    path('college/<int:id>/edit', CrudCollegeView.as_view(), name='college_edit'),
    path('college/<int:id>/delete', CrudCollegeView.as_view(), name='college_delete'),
    path('student/<int:id>/add', CrudStudentView.as_view(), name='college_add_student'),
    path('student/<int:id>/edit', CrudStudentView.as_view(), name='student_edit'),
    path('student/<int:id>/delete', CrudStudentView.as_view(), name='student_delete'),
    path('login/', LoginView.as_view(), name='login'),
    path('signup/', SignupView.as_view(), name='signup'),
    path('logout/', logout_user, name='logout'),
    path('api/v1/colleges', rest_colleges, name='colleges_rest'),
    path('api/v1/colleges/<int:id>', rest_colleges, name='college_rest'),
    path('api/v1/colleges/<int:college_id>/students', StudentRestView.as_view(), name='students_rest'),
    path('api/v1/colleges/<int:college_id>/students/<int:id>', StudentRestView.as_view(), name='student_rest'),
]

from rest_framework.authtoken import views
urlpatterns += [
    path('api-token-auth/', views.obtain_auth_token)
]