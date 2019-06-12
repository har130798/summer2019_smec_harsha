from onlineapp.models import *
from rest_framework import serializers

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('name', 'contact', 'id', 'location', 'acronym')

class CollegeShortSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('acronym',)

class StudentSerializer(serializers.ModelSerializer):
    college = CollegeShortSerializer(read_only=False, many=False)
    class Meta:
        model = Student
        fields = ('name', 'college', 'email', 'dbname', 'id')

class Mocktest1Serializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('problem1', 'problem2', 'problem3', 'problem4', 'total', 'student')

class Mocktest1ShortSerializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('problem1', 'problem2', 'problem3', 'problem4')

class StudentDetailsSerializer(serializers.ModelSerializer):
    mocktest1 = Mocktest1ShortSerializer(read_only=False, many=False)

    class Meta:
        model = Student
        fields = ('name', 'email', 'dbname', 'id', 'mocktest1')

    def create(self, validated_data):

        mocktest_obj = MockTest1(**validated_data.pop('mocktest1'))
        student_obj = Student.objects.create(**validated_data, college_id=self.context['college_id'])
        mocktest_obj.total = sum([
            mocktest_obj.problem1,
            mocktest_obj.problem2,
            mocktest_obj.problem3,
            mocktest_obj.problem4
        ])
        mocktest_obj.student = student_obj
        mocktest_obj.save()

        return student_obj

    def update(self, instance, validated_data):
        mocktest_obj = MockTest1.objects.get(student_id=instance.id)
        mocktest_obj.problem1 = validated_data['mocktest1']['problem1']
        mocktest_obj.problem2 = validated_data['mocktest1']['problem2']
        mocktest_obj.problem3 = validated_data['mocktest1']['problem3']
        mocktest_obj.problem4 = validated_data['mocktest1']['problem4']
        mocktest_obj.total = sum([
            mocktest_obj.problem1,
            mocktest_obj.problem2,
            mocktest_obj.problem3,
            mocktest_obj.problem4
        ])
        instance.name = validated_data['name']
        instance.email = validated_data['email']
        instance.dbname = validated_data['dbname']

        instance.save()
        mocktest_obj.save()

        return instance
