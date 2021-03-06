# Generated by Django 2.2.1 on 2019-06-08 17:01

import datetime
from django.db import migrations, models
import django.db.models.deletion
from django.utils.timezone import utc


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Todolist',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=255)),
                ('created', models.DateTimeField(default=datetime.datetime(2019, 6, 8, 17, 1, 45, 577750, tzinfo=utc))),
            ],
        ),
        migrations.CreateModel(
            name='Todoitem',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('description', models.CharField(max_length=255)),
                ('due_date', models.DateTimeField(blank=True, null=True)),
                ('completed', models.BooleanField(default=False)),
                ('todolist', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='todoapp.Todolist')),
            ],
        ),
    ]
