from django.contrib.auth.models import User, Group
from rest_framework import viewsets
from rest_framework import permissions
from web.serializers import *
from .models import *
from rest_framework.permissions import AllowAny

class DetectionViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows Detections to be viewed or edited.
    """
    queryset = Detection.objects.all().order_by('-datetime')
    serializer_class = DetectionSerializer
    permission_classes = [AllowAny]

class PigeonViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows Pigeons to be viewed or edited.
    """
    queryset = Pigeon.objects.all()
    serializer_class = PigeonSerializer
    permission_classes = [AllowAny]

class RecognitionViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows Recognitions to be viewed or edited.
    """
    queryset = Recognition.objects.all()
    serializer_class = RecognitionSerializer
    permission_classes = [AllowAny]