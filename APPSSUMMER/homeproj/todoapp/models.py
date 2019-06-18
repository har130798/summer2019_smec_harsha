from django.db.models import CharField, DateTimeField, ForeignKey, Model, BooleanField, CASCADE
from django.utils.timezone import *
from django.contrib.auth.models import User
# Create your models here.

class Todolist(Model):
    name = CharField(max_length=255, null=False, blank=False)
    created = DateTimeField(default=now, null=False, blank=False)
    user = ForeignKey(User, null=False, blank=False, on_delete=CASCADE)

    def __str__(self):
        return "{} of {}".format(self.name, self.user.name)

class Todoitem(Model):
    description = CharField(max_length=255, null=False, blank=False)
    due_date = DateTimeField(null=True, blank=True)
    completed = BooleanField(default=False)
    todolist = ForeignKey(Todolist, on_delete=CASCADE)

    def __str__(self):
        return self.description