from django.db import models

# Create your models here.

class Task(models.Model):
    title = models.CharField(max_length=50)
    task = models.CharField(max_length=1000)
    is_complete = models.BooleanField()
    date = models.DateField()

    def __str__(self):
        return self.title

class Person(models.Model):
    name = models.CharField(max_length=255)
    tasks =



