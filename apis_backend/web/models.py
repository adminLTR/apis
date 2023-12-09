from django.db import models

from django.core.validators import FileExtensionValidator 

class Detection(models.Model):
    datetime = models.DateTimeField("Date and time of detection", auto_now_add = True)
    frame = models.ImageField(upload_to = "frames/", null = True) 
    video = models.FileField(upload_to = "videos/", null = True,
        validators = [FileExtensionValidator(allowed_extensions = ['MOV','avi','mp4','webm','mkv'])]
    )
    latitude = models.CharField(max_length = 15)
    longitude = models.CharField(max_length = 15)
    
    def __str__(self):
        return self.datetime
    
    class Meta:
        verbose_name = "Detección"
        verbose_name_plural = "Detecciones"

class Pigeon(models.Model):
    name = models.CharField(max_length = 15)
    description = models.CharField(max_length = 250)
    image = models.ImageField(upload_to = "image/", null = True) 

    def __str__(self):
        return self.name
    
    class Meta:
        verbose_name = "Ave"
        verbose_name_plural = "Aves"

class Recognition(models.Model):
    detection = models.ForeignKey(Detection, on_delete = models.CASCADE)
    pigeon = models.ForeignKey(Pigeon, on_delete = models.CASCADE)
    accuracy = models.FloatField(null = True, blank = True)

    def __str__(self):
        return self.detection
    
    class Meta:
        verbose_name = "Reconocimiento"
        verbose_name_plural = "Reconocimientos"
    