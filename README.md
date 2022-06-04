# rccalendar


## Instalación

### Instala rccalendar

```
curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/c -o \
                   $HOME/.local/bin/c && chmod +x $HOME/.local/bin/c
```

### Paquetes necesarios
- Instalar rclone

```
curl https://rclone.org/install.sh | sudo bash
```

- ncal. Para visualizar el calendario anual

```
sudo apt install ncal
```

## Iniciando
- Lanza el comando `c` y crea un nuevo calendario y archivo de configuración.
- Rellena el archivo de configuración.
- Lanza el comando `c b`, para crear una plantilla para el calendario. Elige el número de dias que desees.
- Ahora puedes crear nuevos eventos en el calendario con la opción `a`, editarlos con `e`, borrarlos con `del`,... 
- Si simplemente lanzas el comando `c`, listará los eventos futuros en las 2 próximas semanas.

Para mas información, pulsa el comando de ayuda `c h`.

## Instalación Termux

```
curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/c -o \
                   $HOME/.config/rccalendar/c && chmod +x $HOME/.config/rccalendar/c
```

## Opciones rccalendar. Calendario en texto plano

Inspirado en un artículo del blog de Tero Karvinen y sobretodo, en el todo.txt de Gina Trapani, nace rccalendar. 
rccalendar es un script en bash para gestionar calendarios en texto plano con el método calendar.txt. 
Es necesario instalar rclone para acceder a los calendarios en tu máquina en local o en la nube.

Opciones disponibles:

```
 Si no escribimos ninguna OPCIÓN, la ternimal nos mostrará los eventos para próximas 2 semanas.
  p       [CALENDARIO]  Mostrar eventos de las próximas 2 semanas, del calendario indicado.               
  
  init                  Crear archivos de configuración. Por defecto, crea un archivo calendar.txt en local  
  b                     Crear plantilla de calendario
  calendar              Calendarios disponibles
  config                Editar archivo de configuración
  update                Mover eventos de la semana anterior al calendar-done.txt. Utilizar un cron semanal cata lunes. Ejem: 01 00  * * 7 c update
  mount                 Montar directorio del calendar.txt y abrir el archivo calendar.txt con el editor del archivo de configuración
  c       [CALENDARIO]  Cambiar de calendario
  calendar              Mostrar calendarios disponibles

Comando para eventos:
 Eventos Futuro. Calendar.txt

  a/add                Añadir tarea en el calendario actual
  a/add  [CALENDARIO]  Añadir tarea en el calendario indicado
  e                    Editar evento futuro del calendario actual
  e      [CALENDARIO]  Editar evento futuro del calendario indicado                    
  del                  Borrar evento futuro
  del    [CALENDARIO]  Borrar evento futuro del calendario indicado

 Eventos pasado. Calendar-done.txt

  ed                   Editar evento pasados del calendario. calendar-done.txt
  ed     [CALENDARIO]  Editar evento pasados del calendario indicado. calendar-done.txt
  deld                 Borrar evento futuro
  deld   [CALENDARIO]  Borrar evento futuro del calendario indicado

Gestión del calendario:
  ls      [PALABRA] [PALABRA]...  Listar todos los eventos futuro del calendario
  lsmd    [PALABRA] [PALABRA]...  Listar todos los eventos futuro del calendario en markdown  
  lsmdall 
  lsall   [PALABRA] [PALABRA]...  Lista todos los eventos futuro y pasado de el archivo calendar.txt + calendar-done.txt

  lsd     [PALABRA] [PALABRA]...  Listar eventos pasados. Archivo calendar-done.txt 

  lsb     [PALABRA] [PALABRA]...  Listar todos los eventos futuro del calendario en bruto
  lsdb    [PALABRA] [PALABRA]...  Listar eventos pasados en bruto. Archivo calendar-done.txt 


  html    [PALABRA] [PALABRA]...  Listar eventos de las próximas 2 semanas en html
  md      [PALABRA] [PALABRA]...  Listar eventos de las próximas 2 semanas en markdown
  org     [PALABRA] [PALABRA]...  Listar eventos futuro en orgmode     

Gestión de todos los calendarios:
  lsc     [CALENDARIO] [PALABRA] [PALABRA]...  Listar todos los eventos futuro del calendario indicado    
  htmlc   [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos de las próximas 2 semanas en html del calendario indicado
  mdc     [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos de las próximas 2 semanas en markdown del calendario indicado
  org     [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos futuro en orgmode del calendario indicado

  lsdc    [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos pasados del calendario indicado. Archivo calendar-done.txt 

  lsb     [CALENDARIO] [PALABRA] [PALABRA]...  Listar todos los eventos futuro en bruto del calendario indicado 
  lsdbc   [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos pasado en bruto del calendario indicado. Archivo calendar-done.txt  

  m       [CALENDARIO]                         Montar directorio del calendar.txt y abrir el archivo calendar.txt con el editor del archivo de configuración
  update  [CALENDARIO]                         Mover eventos de la semana anterior al calendar-done.txt. Utilizar un cron semanal cata lunes. Ejem: 01 00  * * 7 c update
                      01 00  * * 7 c update personal
                      01 00  * * 7 c update trabajo
  cal                                          Muestra un calendario con todos los meses del año actual                      
                      
Envio a otras apps:
  not     [CALENDARIO] [PALABRA] [PALABRA]...  Publicar notificaciones. Aplicación mensajería configurada en calendario.conf. Configura con: c config
  nott    [CALENDARIO] [PALABRA] [PALABRA]...  Mostrar en terminal las notificaciones para eventos de dentro de 7,3,2,1 dias y eventos de hoy.
  lsmds   [CALENDARIO]                         Enviar calendar.txt al archivo markdown añadido en el archivo de configuración. CALENDAR_MD. Archivo actual: $CALENDAR_MD
  
Termux:
  termux                                       Lanza menú para Añadir, Borrar,... Eventos
  termux  [CALENDARIO]                         Lanza menú para Añadir, Borrar,... Eventos del calendario indicado
  termux-install                               Instalación de paquetes necesarios  
```
