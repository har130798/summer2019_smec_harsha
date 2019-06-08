from django.db import models

# Create your models here.

class College(models.Model):
    name = models.CharField(max_length=128)
    acronym = models.CharField(max_length=8)
    location = models.CharField(max_length=64)
    contact = models.EmailField()

    def __str__(self):
        return self.acronym

class Student(models.Model):
    name = models.CharField(max_length=128)
    college = models.ForeignKey(College, on_delete=models.CASCADE) #
    email = models.EmailField(unique=True)
    dbname = models.CharField(max_length=50, unique=True)

    def __str__(self):
        return self.name


class MockTest1(models.Model):
    student = models.OneToOneField(Student, on_delete=models.CASCADE)
    problem1 = models.IntegerField()
    problem2 = models.IntegerField()
    problem3 = models.IntegerField()
    problem4 = models.IntegerField()
    total = models.IntegerField()


    def __str__(self):
        return f"Student {self.student.name} marks"


class Teacher(models.Model):
    name = models.CharField(max_length=40)
    college = models.ForeignKey(College, on_delete=models.CASCADE)