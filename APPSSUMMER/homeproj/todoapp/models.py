from django.db.models import *
from django.utils.timezone import *
# Create your models here.

class Todolist(Model):
    name = CharField(max_length=255, null=False, blank=False)
    created = DateTimeField(default=now, null=False, blank=False)

    def __str__(self):
        return self.name

class Todoitem(Model):
    description = CharField(max_length=255, null=False, blank=False)
    due_date = DateTimeField(null=True, blank=True)
    completed = BooleanField(default=False)
    todolist = ForeignKey(Todolist, on_delete=CASCADE)

    def __str__(self):
        return self.description