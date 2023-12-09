from django.contrib import admin

from .models import Detection, Pigeon, Recognition

admin.site.register(Detection)
admin.site.register(Pigeon)
admin.site.register(Recognition)
