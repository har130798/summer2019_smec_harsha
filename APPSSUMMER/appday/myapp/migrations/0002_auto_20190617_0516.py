# Generated by Django 2.2.1 on 2019-06-17 05:16

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('myapp', '0001_initial'),
    ]

    operations = [
        migrations.RenameField(
            model_name='match',
            old_name='player_of_the_match',
            new_name='player_of_match',
        ),
    ]
