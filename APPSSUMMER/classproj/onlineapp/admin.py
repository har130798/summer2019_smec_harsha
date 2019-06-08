from django.contrib import admin
from .models import College, Student, Teacher, MockTest1

# Register your models here.
admin.site.register(College)
admin.site.register(Student)
admin.site.register(Teacher)
admin.site.register(MockTest1)
