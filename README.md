# Modelos_tesis
Repositorio asociado a la tesis de maestría:
"DESARROLLO DE UN DISPOSITIVO PARA LA DETECCIÓN Y REPORTE DE COMPORTAMIENTOS DE RIESGO DENTRO DE LA CABINA DURANTE LA CONDUCCIÓN DE VEHÍCULOS TERRESTRES".

Autor: Juan Manuel Calvo Duque
Fecha: 2025

## Descripción General
Este repositorio contiene todos los scripts, configuraciones y firmwares desarrollados para:

* Automatizar la captura de imágenes desde el dispositivo AMB82-Mini.

* Preparar y organizar el conjunto de datos de entrenamiento, validación y prueba.

* Entrenar modelos ligeros de detección de objetos (YOLOv3-Tiny, YOLOv4-Tiny, YOLOv7-Tiny) en Google Colab utilizando GPU (T4, L4).
  
* Realizar la evaluación práctica de los modelos directamente sobre el dispositivo, usando streaming de video en tiempo real (RTSP) para validación visual.

Todo el trabajo está orientado a lograr una detección eficiente de microsueños, distracción visual y uso de celular en conductores, dentro de escenarios de conducción urbana controlada.

## Estructura del Repositorio

```plaintext
Modelos_tesis/
│
├── scripts_preparacion/
│   ├── division_dataset.py          # División del dataset en train/val/test
│   ├── captura_imagenes_AMB82.ino    # Firmware para captura de imágenes con AMB82-Mini
│
├── scripts_entrenamiento/
│   ├── entrenamiento_yolov3.py       # Entrenamiento YOLOv3-Tiny
│   ├── entrenamiento_yolov4.py       # Entrenamiento YOLOv4-Tiny
│   ├── entrenamiento_yolov7.py       # Entrenamiento YOLOv7-Tiny
│   └── archivos_config/              # Configuraciones (.cfg, .yaml)
│       ├── yolov3-tiny.cfg
│       ├── yolov4-tiny.cfg
│       └── yolov7-tiny.yaml
│
├── scripts_evaluacion/
│   ├── evaluacion_rtsp_AMB82.ino      # Firmware para inferencia RTSP
│
└── README.md                         # Este documento




