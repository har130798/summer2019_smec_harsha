import os, django, click

os.environ.setdefault('LANG', 'en_US.UTF-8')
os.environ.setdefault('LC_ALL', 'en_US.UTF-8')
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'homeproj.settings')
django.setup()

from todoapp.models import *

DATA_FILE = 'data.txt'

@click.command()
def populate():
    file = open(DATA_FILE, 'r')
    lines = file.readlines()
    numberOfTodolists, numberOfTodoItemsPerList = [int(x) for x in lines[0].split()]
    index = 1
    # for i in range(numberOfTodolists):
    #     t = Todolist(name=lines[index])
    #     index += 1
    #     t.save()

    index = numberOfTodolists + 1
    id = 1
    for i in range(numberOfTodolists * numberOfTodoItemsPerList):
        t = Todolist.objects.get(id=id)
        id += 1
        for j in range(numberOfTodoItemsPerList):
            line = lines[index].split()
            index += 1
            ti = Todoitem(description=line[0], completed=line[-1], todolist=t)
            ti.save()

    file.close()
    print("Populated!")

if __name__ == '__main__':
    populate()