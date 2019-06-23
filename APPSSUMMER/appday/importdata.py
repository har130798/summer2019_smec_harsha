import csv
import os
import django

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'appday.settings')
django.setup()

from myapp.models import *

with open('deliveries.csv','rt')as f:
    data = csv.DictReader(f)
    for row in data:
        match = Delivery(**row)
        match.save()