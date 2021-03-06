from onlineapp.models import *
from onlineapp.serializers import *
from rest_framework.response import Response
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.status import *
from rest_framework.views import APIView
from rest_framework.authentication import SessionAuthentication, BasicAuthentication, TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from django.conf import settings
from django.db.models.signals import post_save
from django.dispatch import receiver
from rest_framework.authtoken.models import Token

@api_view(['GET', 'POST', 'DELETE', 'PUT'])
@authentication_classes((SessionAuthentication, BasicAuthentication, TokenAuthentication))
@permission_classes((IsAuthenticated,))
def rest_colleges(request, *args, **kwargs):

    if request.method == 'POST':
        serializer = CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=HTTP_201_CREATED)
        return Response(serializer.errors, status=HTTP_400_BAD_REQUEST)

    elif request.method == 'PUT':
        try:
            college = College.objects.get(**kwargs)
            serializer = CollegeSerializer(college, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=HTTP_201_CREATED)
        except Exception as e:
            print(e)
        return Response(status=HTTP_400_BAD_REQUEST)


    elif request.method == 'DELETE':
        try:

            College.objects.get(**kwargs).delete()

        except Exception as e:
            print(e)
            return Response(status=HTTP_400_BAD_REQUEST)

        return Response(status=HTTP_202_ACCEPTED)

    if kwargs:
        try:
            college = College.objects.get(**kwargs)
        except Exception as e:
            print(e)
            return Response(status=404)
        serialized = CollegeSerializer(college)
        return Response(serialized.data)

    colleges = College.objects.all()
    serialized = CollegeSerializer(colleges, many=True)

    return Response(serialized.data)

class StudentRestView(APIView):
    authentication_classes = (SessionAuthentication, BasicAuthentication, TokenAuthentication)
    permission_classes = (IsAuthenticated,)

    def get(self, request, *args, **kwargs):
        try:
            if kwargs.get('id') != None:
                student = Student.objects.get(**kwargs)
                return Response(StudentSerializer(student).data)

            students = StudentSerializer(Student.objects.filter(**kwargs), many=True)
            return Response(students.data)
        except Exception as e:
            print(e)
            return Response(status=HTTP_400_BAD_REQUEST)

    def post(self, request, *args, **kwargs):
        details = StudentDetailsSerializer(data=request.data, context={
            'college_id' : kwargs.get('college_id')
        })

        if details.is_valid():
            details.save()
            return Response(details.data)

        return Response(details.error_messages, status=HTTP_400_BAD_REQUEST)

    def delete(self, request, *args, **kwargs):
        try:
            Student.objects.get(id=kwargs.get('id')).delete()
            return Response(status=HTTP_202_ACCEPTED)
        except Exception as e:
            return Response(status=HTTP_400_BAD_REQUEST)

    def put(self, request, *args, **kwargs):
        try:
            student = Student.objects.get(id=kwargs.get('id'))
            serializer = StudentDetailsSerializer(instance=student, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=HTTP_201_CREATED)
        except Exception as e:
            print(e)
        return Response(status=HTTP_400_BAD_REQUEST)

@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def create_auth_token(sender, instance=None, created=False, **kwargs):
    if created:
        Token.objects.create(user=instance)