from rest_framework.views import APIView
from rest_framework.response import Response
from todoapp.serializer import *
from rest_framework.authentication import BasicAuthentication, SessionAuthentication, TokenAuthentication
from rest_framework.permissions import IsAuthenticated

#TODO Return query exception based status code for failed requests

class TodolistRestView(APIView):

    authentication_classes = (BasicAuthentication, SessionAuthentication, TokenAuthentication)
    permission_classes = (IsAuthenticated, )

    def get(self, request, *args, **kwargs):
        if kwargs:
            try:
                todolist = Todolist.objects.get(**kwargs, user_id=request.user.id)
                serializer = TodolistSerializer(todolist)
                return Response(serializer.data)
            except Exception as e:
                if type(e) is Todolist.DoesNotExist:
                    return Response(status=404)
                return Response(status=400)


        todolists = Todolist.objects.filter(user_id=request.user.id)
        serializer = TodolistSerializer(todolists, many=True)

        return Response(serializer.data)

    def post(self, request, *args, **kwargs):

        serializer = TodolistSerializer(data=request.data)

        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)

        return Response(serializer.errors)

    def put(self, request, *args, **kwargs):
        try:
            todolist = Todolist.objects.get(**kwargs)
        except Exception as e:
            if type(e) is Todolist.DoesNotExist:
                return Response(status=404)
            return Response(status=400)

        serializer = TodolistSerializer(instance=todolist, data=request.data)

        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)

        return Response(serializer.errors, status=404)

    def delete(self, request, *args, **kwargs):
        try:

            Todolist.objects.get(**kwargs).delete()
            return Response(status=202)

        except Exception as e:
            if type(e) is Todolist.DoesNotExist:
                return Response(status=404)
            return Response(status=400)



class TodoitemRestView(APIView):

    authentication_classes = (BasicAuthentication, SessionAuthentication, TokenAuthentication)
    permission_classes = (IsAuthenticated,)

    def get(self, request, *args, **kwargs):
        if 'id' in kwargs.keys():
            try:
                todoitem = Todoitem.objects.get(**kwargs, todolist_user_id=request.user.id)
                serializer = TodoitemSerializer(todoitem)
            except Exception as e:
                if type(e) is Todoitem.DoesNotExist:
                    return Response(status=404)
                return Response(status=400)

            return Response(serializer.data)

        todoitems = Todoitem.objects.filter(**kwargs, todolist_user_id=request.user.id)
        serializer = TodoitemSerializer(todoitems, many=True)

        return Response(serializer.data)

    def post(self, request, *args, **kwargs):
        serializer = TodoitemSerializer(data=request.data)

        if serializer.is_valid():
            serializer.save()

            return Response(serializer.data)

        return Response(serializer.errors)

    def put(self, request, *args, **kwargs):
        try:
            todoitem = Todoitem.objects.get(**kwargs, todolist_user_id=request.user.id)
        except Exception as e:
            if type(e) is Todoitem.DoesNotExist:
                return Response(status=404)
            return Response(status=400)

        serializer = TodoitemSerializer(instance=todoitem, data=request.data)

        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)

        return Response(serializer.errors)

    def delete(self, request, **kwargs):

        try:
            Todoitem.objects.get(**kwargs, todolist_user_id=request.user.id).delete()
            return Response(status=202)
        except Exception as e:
            if type(e) is Todoitem.DoesNotExist:
                return Response(status=404)
            return Response(status=400)