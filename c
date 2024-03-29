#!/bin/bash
#
#  rccalendar
#  Copyright (c) 2022 uGeek
#
VERSION="v0.4.7 20/11/2022"
# - 0.4.7 Opción de instalación install e install termux
# - 0.4.6 Añadir desde la terminal en termux tareas y geolocalización
# - 0.4.5 Impotación i
# - 0.4.4 Añadido comando clear y ip
#
#
#


mkdir -p ~/.config/rccalendar ~/.config/rccalendar/mount


if [ "$1" = "-U" ]
then
    mkdir -p $HOME/.local/bin
    echo "alias c='bash ~/.local/bin/c'" >> $HOME/.bashrc
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/c -o  $HOME/.local/bin/c && chmod +x $HOME/.local/bin/c
    exit
fi

if [ "$1" = "install" ]
then
    mkdir -p $HOME/.local/bin
    echo "alias c='bash ~/.local/bin/c'" >> $HOME/.bashrc
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/c -o  $HOME/.local/bin/c && chmod +x $HOME/.local/bin/c
    mkdir -p $HOME/.config/rccalendar/
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/.config/rccalendar/personal.sample.conf -o  $HOME/.config/rccalendar/personal.sample.conf
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/.config/rccalendar/rccalendar.pg -o  $HOME/.config/rccalendar/rccalendar.sample.pg
   ### paquetes
    sudo apt install curl bc ncal -y
    curl https://rclone.org/install.sh | sudo bash
    clear
    echo "Edita el archivo de configuración: $HOME/.config/rccalendar/personal.conf"
    echo "renombra rccalendar.sample.pg por rccalendar.pg"
    exit
fi

if [ "$1" = "install" ] || [ "$2" = "termux" ]
then
    mkdir -p $HOME/.local/bin
    echo "alias c='bash ~/.local/bin/c'" >> $HOME/.bashrc
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/c -o $HOME/.local/bin/c && chmod +x $HOME/.local/bin/c
    mkdir -p $HOME/.config/rccalendar/
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/.config/rccalendar/personal.sample.conf -o  $HOME/.config/rccalendar/personal.sample.conf
    curl -L https://raw.githubusercontent.com/uGeek/rccalendar/main/.config/rccalendar/rccalendar.pg -o  $HOME/.config/rccalendar/rccalendar.sample.pg
    ### Termux 
    pkg upgrade
    pkg install jq termux-api termux-services rclone -y
    mkdir -p ~/.shortcuts
    echo "bash ~/.config/rccalendar/c termux" > ~/.shortcuts/Calendario
    clear
    echo "Edita el archivo de configuración: $HOME/.config/rccalendar/personal.sample.conf"
    echo "renombra rccalendar.sample.pg por rccalendar.pg"
    exit
fi



if [ "$1" = "init" ]
then
echo "Introduce el nombre del calendario: " ; read CALENDARIO
echo "Creado archivo de configuración $CALENDARIO.conf"
echo "
# Nombre de Archivos del calendario
CALFILE='calendar.txt'

# Ruta del archivo del calendario
CAL='local:$HOME/.config/rccalendar/calendar/calendar.txt'

# Archivo done
CAL_DONE='local:$HOME/.config/rccalendar/calendar/calendar-done.txt'

# Directorios de los calendarios
CALENDARDIR='local:$HOME/.config/rccalendar/calendar/'


# Archivos de exportación en Markdown, OrgMode,...
TITLEORG='0. CALENDARIO'
CALENDAR_ORG='webdav:calendar/org/calendario.org'

CALENDAR_MD='webdav:Notas/calendar_dashboard.md'

# Editor de texto, para editar calendar
EDITOR='nano'

# Notificaciones. Dentro de la función notification
#function notification {
### añade aquí el código para las notificiones
#}
" > $HOME/.config/rccalendar/$CALENDARIO.conf
echo "source ~/.config/rccalendar/$CALENDARIO.conf" > ~/.config/rccalendar/source
touch ~/.config/rccalendar/rccalendar.pg
mkdir -p ~/.config/rccalendar/calendar
touch $HOME/.config/rccalendar/calendar/calendar-done.txt $HOME/.config/rccalendar/calendar/calendar-done.txt
source ~/.config/rccalendar/$CALENDARIO.conf
$EDITOR $HOME/.config/rccalendar/$CALENDARIO.conf
            clear
    exit
    fi


if [ "$1" = "c" ]
then

    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	    echo "No existe este calendario. Crealo con la opción: init"
	exit
	fi
   

    
    echo "source ~/.config/rccalendar/$2.conf" >  ~/.config/rccalendar/source
    source ~/.config/rccalendar/$2.conf
    echo " calendar.txt $(cat ~/.config/rccalendar/source | cut -d "/" -f4 |  cut -d "." -f1)"    
    exit
fi

source ~/.config/rccalendar/source
source ~/.config/rccalendar/rccalendar.pg

if [ "$1" = "h" ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]
then    
clear
echo "Modo de empleo: c [OPCIÓN] [PALABRA A FILTRAR / CALENDARIO] ...

rccalendar. Calendario en texto plano
--------------------------------------------
Inspirado en un artículo del blog de Tero Karvinen y sobretodo, en el todo.txt de Gina Trapani, nace rccalendar. 
rccalendar es un script en bash para gestionar calendarios en texto plano con el método calendar.txt. 
Es necesario instalar rclone para acceder a los calendarios en tu máquina en local o en la nube.

Opciones disponibles:
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
  orgs                                         Enviar calendario a archivo orgmode
                                               cron: c c personal ;  c orgs
  lsdc    [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos pasados del calendario indicado. Archivo calendar-done.txt 

  lsb     [CALENDARIO] [PALABRA] [PALABRA]...  Listar todos los eventos futuro en bruto del calendario indicado 
  lsdbc   [CALENDARIO] [PALABRA] [PALABRA]...  Listar eventos pasado en bruto del calendario indicado. Archivo calendar-done.txt  

  m       [CALENDARIO]                         Montar directorio del calendar.txt y abrir el archivo calendar.txt con el editor del archivo de configuración
  update  [CALENDARIO]                         Mover eventos de la semana anterior al calendar-done.txt. Utilizar un cron semanal cata lunes. Ejem: 01 00  * * 7 c update
                      01 00  * * 7 c update personal
                      01 00  * * 7 c update trabajo

  cal                                          Muestra un calendario con todos los meses del año actual    

  clear                                        Elimina días sin eventos

  f                                            Añadir Eventos, festivos entre 2 fechas
  i                                            Importar eventos.
                                               La fecha tiene que guardar el formato 2022-01-20
                                                  Ejemplo de importación: c i /home/usuario/eventos.txt

  ip                                           Importar desde plantilla. Solo año actual. Ideal para festivos. 
                                               Formato fecha 01-22
                                                  Ejemplo de importación: c ip /home/usuario/festivos.txt 


Envio a otras apps:
  calendarweb  [CALENDARIO]                    Crear calendario web con eventos en el calendario   
  not     [CALENDARIO] [PALABRA] [PALABRA]...  Publicar notificaciones. Aplicación mensajería configurada en calendario.conf. Configura con: c config
  nott    [CALENDARIO] [PALABRA] [PALABRA]...  Mostrar en terminal las notificaciones para eventos de dentro de 7,3,2,1 dias y eventos de hoy.
  lsmds   [CALENDARIO]                         Enviar calendar.txt al archivo markdown añadido en el archivo de configuración. CALENDAR_MD. Archivo actual: $CALENDAR_MD
  

Termux:
  atermux                                      Lanza menú para Añadir eventos. Versión terminal
  termux                                       Lanza menú para Añadir, Borrar,... Eventos
  termux  [CALENDARIO]                         Lanza menú para Añadir, Borrar,... Eventos del calendario indicado
  termux-install                               Instalación de paquetes necesarios  

Instalación
  install                                      Instalación en distros ubuntu,debian,...
  install termux                               Instalación en termux para android
  -U                                           Actualización de rccalendar

Valores del archivo de configuración, del calendario actual:
  
  Calendar.txt              = $CAL
  Calendar-done.txt         = $CAL_DONE
  Directorio del Calendario = $CALENDARDIR
  
  Título del OrgMode = $TITLEORG
  Archivo OrgMode    = $CALENDAR_ORG
  Archivo Markdown   = $CALENDAR_MD
  
  Editor = $EDITOR


rccalendar $VERSION
Copyright (C) 2020-2022 Angel. uGeek
 ugeekpodcast@gmail.com

"
exit
fi

if [ "$1" = "config" ]
then
    if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    $EDITOR ~/.config/rccalendar/$2.conf
    exit    
    fi    
    $EDITOR ~/.config/rccalendar/$(cat ~/.config/rccalendar/source |  sed 's/.*\///'  | cut -d "." -f1).conf
    exit
    fi  


if [ "$1" = "b" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
echo -en "¿Cuantos días quieres que cree?: " ; read VECES
DIAS=0
function construir {
date +'%Y-%m-%d W%V %a' --date "$(date +'%Y-%m-%d') +$DIAS day"
while [ "$VECES" -gt "0" ];
do
  DIAS=$(($DIAS+1))
  date +'%Y-%m-%d W%V %a' --date "$(date +'%Y-%m-%d') +$DIAS day"
  VECES=$(($VECES-1))
done
}
FILE=$(construir)
echo "$FILE" | rclone rcat $CAL
exit
fi


if [ "$1" = "mount" ]
then

if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
mkdir -p  ~/.config/rccalendar/mount
rclone mount $CALENDARDIR ~/.config/rccalendar/mount  > /dev/null 2>&1 &
sleep 5s
$EDITOR  ~/.config/rccalendar/mount/$CALFILE
fusermount -uz ~/.config/rccalendar/mount/
exit
fi


if [ "$1" = "calendarweb" ] 
then

    if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi


    
    CALENDAR_RC=$(rclone cat $CAL |& grep "W")
    CALENDAR_PAS=$(rclone cat $CAL_DONE |& grep "W")
clear
echo ""
PAS=$(while read LINEA; do
    echo -e $(echo "$CALENDAR_PAS" | sed -n "$LINEA"p)
	 done <<< $(echo "$CALENDAR_PAS" | cut -d " " -f4- | grep . -n | cut -d ":" -f1))


FUTURE=$(while read LINEA; do
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p)
	 done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1))
echo -e "$PAS"\n"$FUTURE" | rclone rcat $CALENDAR_WEB
exit
fi



if [ "$1" = "clear" ] 
then

    if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi


    
    CALENDAR_RC=$(rclone cat $CAL |& grep "W")
    CALENDAR_PAS=$(rclone cat $CAL_DONE |& grep "W")
clear
echo ""
echo "Eliminados días sin eventos"

PAS=$(while read LINEA; do
    echo -e $(echo "$CALENDAR_PAS" | sed -n "$LINEA"p)
	 done <<< $(echo "$CALENDAR_PAS" | cut -d " " -f4- | grep . -n | cut -d ":" -f1))
echo  "$PAS" | rclone rcat $CAL_DONE


FUTURE=$(while read LINEA; do
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p)
	 done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1))
echo  "$FUTURE" | rclone rcat $CAL
exit
fi




if [ "$1" = "ls" ] 
then 
CALENDAR_RC=$(rclone cat $CAL |& grep "W"  | grep -i "$2" | grep -i "$3" | grep -i "$4")
clear
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-)  | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "lsall" ] 
then    
CALENDAR=$(rclone cat $CAL |& grep "W" | grep -i "$2" | grep -i "$3" | grep -i "$4")
CALENDAR_DONE=$(rclone cat $CAL_DONE |& grep "W" | grep -i "$2" | grep -i "$3" | grep -i "$4" )
CALENDAR_RC=$(echo -e "$CALENDAR_DONE\n$CALENDAR")
clear
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-)  | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""

done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n  | cut -d ":" -f1)
exit
fi

if [ "$1" = "lsc" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    
CALENDAR_RC=$(rclone cat $CAL |& grep "W" | grep -i "$3" | grep -i "$4" | grep -i "$5" )
clear
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/→/\n/g' | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "html" ]
then
CALENDAR_RC=$(rclone cat $CAL |& egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")" | grep -i "$2" | grep -i "$3" | grep -i "$4")
clear
echo ""
while read LINEA; do 
    echo "<b> $(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y')</b>"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/>> /' | sed 's/\\n/ >> /'
    echo "<br>"
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "htmlc" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    
CALENDAR_RC=$(rclone cat $CAL |& egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")" | grep -i "$3" | grep -i "$4" | grep -i "$5")
clear
echo ""
while read LINEA; do  
    echo "<b> $(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y')</b>"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/>> /' | sed 's/\\n/ >> /'
    echo "<br>"
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "md" ] 
then
CALENDAR_RC=$(rclone cat $CAL |& egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")" | grep -i "$2" | grep -i "$3" | grep -i "$4" )
clear
echo ""
while read LINEA; do    
    echo "##### $(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y')"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/- /' | sed 's/\\n/ - /'
    echo " "
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "mdc" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
CALENDAR_RC=$(rclone cat $CAL |& egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")" | grep -i "$3" | grep -i "$4" | grep -i "$5" )
clear
echo ""
while read LINEA; do
    echo "##### $(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y')"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/- /' | sed 's/\\n/ - /'
    echo " "
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n  | cut -d ":" -f1)
exit
fi

if [ "$1" = "lsdb" ] 
then
rclone cat $CAL_DONE  | grep -i "$2"  | grep -i "$3"  | grep -i "$4"
exit
fi

if [ "$1" = "lsdbc" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi    
rclone cat $CAL_DONE  | grep -i "$3"  | grep -i "$4"  | grep -i "$5"
exit
fi

if [ "$1" = "lsd" ] 
then
CALENDAR_RC=$(rclone cat $CAL_DONE |& grep "W"  | grep -i "$2"  | grep -i "$3"  | grep -i "$4")
clear
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "lsdc" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi    
CALENDAR_RC=$(rclone cat $CAL_DONE |& grep "W" | grep -i "$3"  | grep -i "$4"  | grep -i "$5")
clear
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n |  cut -d ":" -f1)
exit
fi

if [ "$1" = "update" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi
echo "Moviendo eventos de la semana anterior a calendar-done.txt"
echo -ne "$(rclone cat $CAL |& grep "$(date --date='-1 week' +"W%V")")"
echo -ne "$(rclone cat $CAL_DONE)\n$(rclone cat $CAL |& grep "$(date --date='-1 week' +"W%V")")" | rclone rcat $CAL_DONE    
rclone cat $CAL |& grep -v "$(date --date='-1 week' +"W%V")" | rclone rcat $CAL
exit
fi

if [ "$1" = "org" ]
then


if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi    
    
    
CALENDAR_RC=$(rclone cat $CAL |& grep "W" | grep -i "$2"  | grep -i "$3"  | grep -i "$4")
echo ""
while read LINEA; do
    FECHA=$(echo "SCHEDULED: <$(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%Y-%m-%d %a')>")
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/* /' |  sed 's/$/\n'"$FECHA"' /'
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "orgc" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi    
CALENDAR_RC=$(rclone cat $CAL2 |& grep "W" | grep -i "$3"  | grep -i "$4"  | grep -i "$5" )
echo ""
while read LINEA; do
    FECHA=$(echo "SCHEDULED: <$(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%Y-%m-%d %a')>")
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/* /' |  sed 's/$/\n'"$FECHA"' /'   
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | grep "$3" | cut -d ":" -f1)
exit
fi


if [ "$1" = "orgs" ] 
then

echo -e "#+TITLE:$TITLEORG\n$(c org $2)" | rclone rcat $CALENDAR_ORG

exit
fi



if [ "$1" = "lsdb" ] 
then
rclone cat $CAL_DONE  | grep -i "$2"  | grep -i "$3"  | grep -i "$4"
exit
fi



if [ "$1" = "lsdbc" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    
rclone cat $CAL_DONE  | grep -i "$3"  | grep -i "$4"  | grep -i "$5"
exit
fi

if [ "$1" = "not" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
    if [ "$(c nott "$2")" != "" ]
    then
	MENSAJE=$(c nott "$2")
	notification
    fi
    exit
fi

if [ "$1" = "nott" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
echo ""
CALENDART=$(rclone cat $CAL)
CALENDAR_RC=$(echo "$CALENDART" | grep $(date +%Y-%m-%d))
if [ "$(echo $CALENDAR_RC | cut -d " " -f4-)" != "" ] 
then 
echo "Hoy, $(date -d "$(echo $CALENDAR_RC | cut -d " " -f1)" +'%A %d de %B del %Y')"
echo "---------------------------------------------------------"
echo -e "$(echo $CALENDAR_RC | cut -d " " -f4-)" | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
echo ""
fi

CALENDAR_RC=$(echo "$CALENDART" | grep $(date --date='+1 day' +%Y-%m-%d))
if [ "$(echo $CALENDAR_RC | cut -d " " -f4-)" != "" ] 
then 
echo "Mañana, $(date -d "$(echo $CALENDAR_RC | cut -d " " -f1)" +'%A %d de %B del %Y')"
echo "---------------------------------------------------------"
echo -e "$(echo $CALENDAR_RC | cut -d " " -f4-)" | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
echo ""
fi

echo ""
CALENDAR_RC=$(echo "$CALENDART" | grep $(date --date='+2 day' +%Y-%m-%d))
if [ "$(echo $CALENDAR_RC | cut -d " " -f4-)" != "" ] 
then 
echo "En dos dias, $(date -d "$(echo $CALENDAR_RC | cut -d " " -f1)" +'%A %d de %B del %Y')"
echo "---------------------------------------------------------"
echo -e "$(echo $CALENDAR_RC | cut -d " " -f4-)" | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
echo ""
fi

echo ""
CALENDAR_RC=$(echo "$CALENDART" | grep $(date --date='+7 day' +%Y-%m-%d))
if [ "$(echo $CALENDAR_RC | cut -d " " -f4-)" != "" ] 
then 
echo "En 7 dias, $(date -d "$(echo $CALENDAR_RC | cut -d " " -f1)" +'%A %d de %B del %Y')"
echo "---------------------------------------------------------"
echo -e "$(echo $CALENDAR_RC | cut -d " " -f4-)" | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
echo ""
fi
exit
fi

if [ "$1" = "e" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi         
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA    
read -e -p "Mes: " -i "$(date  +'%m')" MES    
read -e -p "Año: " -i "$(date  +'%Y')" ANO    
clear   
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

if [ "$(echo "$TODO" | grep "^$CALDIA")" = "" ]
then
echo ""
echo "Esta fecha no está en la plantilla del calendario"
echo ""
echo "  Edita fechas pasadas con: c ed"
echo ""
exit
fi

read -e -p "Evento a editar: " -i "$(echo "$TODO" | grep -i "$CALDIA" )" RESPUESTA
echo ""
echo ""
TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
exit
fi

if [ "$1" = "lo" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi         
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA    
read -e -p "Mes: " -i "$(date  +'%m')" MES    
read -e -p "Año: " -i "$(date  +'%Y')" ANO    
clear   
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

if [ "$(echo "$TODO" | grep "^$CALDIA")" = "" ]
then
echo ""
echo "Esta fecha no está en la plantilla del calendario"
echo ""
echo "  Edita fechas pasadas con: c ed"
echo ""
exit
fi

echo "Abriendo $(echo "$TODO" | grep -i "$CALDIA" | egrep -o 'https?://[^ ]+')"
xdg-open $(echo "$TODO"  | sed -n "$TASK"p | egrep -o 'https?://[^ ]+')


exit
fi


if [ "$1" = "old" ]
then

CALENDAR=$(rclone cat $CAL |& grep "W" | grep -i "$2" | grep -i "$3" | grep -i "$4")
CALENDAR_DONE=$(rclone cat $CAL_DONE |& grep "W" | grep -i "$2" | grep -i "$3" | grep -i "$4" )
CALENDAR_RC=$(echo -e "$CALENDAR_DONE\n$CALENDAR")
clear
echo ""

EVENT=$(while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-)  | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""

	done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n  | cut -d ":" -f1)
     )

echo "$EVENT"




#    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
#read -e -p "Evento a editar: " -i "$(echo "$TODO" | grep -i "$CALDIA" )" RESPUESTA
echo ""
echo ""

echo "$EVENT" |  grep "http"  |  nl -s "- "
exit
echo ""
echo "$EVENT" |  grep "http"  | egrep -o 'https?://[^ ]+'  | nl -s "- "
echo ""
#echo -n "Selecciona un enlace: " ; read -e ENLACE
#echo ""
#echo "Abriendo $(echo "TODO" | grep -i "$CALDIA" | grep "http"  | egrep -o 'https?://[^ ]+') | sed -n "$ENLACE"p)"
#
exit									     




echo "Abriendo $(echo "$TODO" | grep -i "$CALDIA" | egrep -o 'https?://[^ ]+')"
xdg-open $(echo "$TODO"  | sed -n "$TASK"p | egrep -o 'https?://[^ ]+')

    echo ""
exit
fi





if [ "$1" = "ed" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi         
TODO="$(rclone cat $CAL_DONE |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA    
read -e -p "Mes: " -i "$(date  +'%m')" MES    
read -e -p "Año: " -i "$(date  +'%Y')" ANO    
clear   
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
read -e -p "Evento a editar: " -i "$(echo "$TODO" | grep -i "$CALDIA" )" RESPUESTA
echo ""
echo ""
TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL_DONE
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
exit
fi


function addevent {
    if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1)")" = "" ]
then
   NEWCALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d W%W %a')
   echo -e "$(rclone cat "$CAL")\n$(echo "$NEWCALDIA")" | sort | rclone rcat $CAL
   TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
    fi


if [ "$(echo "$TODO" | grep "^$CALDIA")" = "" ]
then
    echo ""
    echo "Esta fecha no está en la plantilla del calendario"
    echo ""
    echo "  Edita fechas pasadas con: c ed"
    echo ""
    exit
fi


if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    echo "Ya hay un evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
    echo ""
    echo ""
else
    echo ""
fi

####
if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    ## Ya hay un evento
    echo ""
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA) → $HORA $EVENT $ADDTAG $ADDCON")
    echo ""
    echo ""
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
else
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $HORA $EVENT $ADDTAG $ADDCON")
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
fi
LOGADD=$(echo "$(date +'%Y/%m/%d %T')  :  ADD EVENT \t $HORA $EVENT $ADDTAG $ADDCON")
echo -ne "$(rclone cat $LOGS)\n$(echo "$LOGADD")" | rclone rcat $LOGS
}


function add_contexto_proyecto {
    
 echo -en "Quieres añadir un proyecto preestablecido?: " ; read RESPUESTA
 
 if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
 then
     TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " +\w" | cut -d"+" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
     echo ""
     echo "Etiquetas ya creadas: "
     echo "$TAGS" |  nl -s '. '
     echo ""
     echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
     echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
     ADDTAG="$(echo +$(echo "$TAGS" | sed -n "$NUM"p))"
 fi
 #######
 echo -en "Quieres añadir un contextos preestablecido?: " ; read RESPUESTA
 if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
 then
     TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " @\w" | cut -d"@" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
     echo ""
     echo "Contextos ya creadas: "
     echo "$TAGS" |  nl -s '. '
     echo ""
     echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
     echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
     ADDCON="$(echo @$(echo "$TAGS" | sed -n "$NUM"p))"
 fi
}



if [ "$1" = "f" ]  
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi


TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
clear
echo ""
echo "Dia de Inicio"
echo "-------------"
read -e -p "Día: " -i "$(date  +'%d')" DIA      
read -e -p "Mes: " -i "$(date  +'%m')" MES      
read -e -p "Año: " -i "$(date  +'%Y')" ANO      
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
INICIO=$(date -d "$(echo "$CALDIA")" +'%d/%m/%Y')

###
echo

echo "Día de Finalización"
echo "-------------------"
read -e -p "Día: " -i "$(date  +'%d')" DIAFIN      
read -e -p "Mes: " -i "$(date  +'%m')" MESFIN      
read -e -p "Año: " -i "$(date  +'%Y')" ANOFIN      
CALDIAFIN=$(date -d "$(echo "$ANOFIN-$MESFIN-$DIAFIN")" +'%Y-%m-%d')
FIN=$(date -d "$(echo "$CALDIAFIN")" +'%d/%m/%Y')


###
echo ""
echo -en "Nuevo evento: " ; read -e IN_EVENT

### Añadir contexto o proyecto
 echo -en "Quieres añadir un proyecto preestablecido?: " ; read RESPUESTA
 
 if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
 then
     TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " +\w" | cut -d"+" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
     echo ""
     echo "Etiquetas ya creadas: "
     echo "$TAGS" |  nl -s '. '
     echo ""
     echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
     echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
     ADDTAG="$(echo +$(echo "$TAGS" | sed -n "$NUM"p))"
 fi
 #######
 echo -en "Quieres añadir un contextos preestablecido?: " ; read RESPUESTA
 if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
 then
     TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " @\w" | cut -d"@" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
     echo ""
     echo "Contextos ya creadas: "
     echo "$TAGS" |  nl -s '. '
     echo ""
     echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
     echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
     ADDCON="$(echo @$(echo "$TAGS" | sed -n "$NUM"p))"
 fi
 

DIASTOTAL=$(echo "(`date -u --date=$CALDIAFIN +%s`-`date -u --date=$CALDIA +%s`)/86400"+1 | bc)
EVENT=$(echo "Inicio de $IN_EVENT. Finalización el día $FIN. $DIASTOTAL días en total "$ADDTAG" "$ADDCON"")

addevent

TODO="$(rclone cat $CAL |  sed '/^ *$/d')"

DIA=$(echo $DIAFIN)
MES=$(echo $MESFIN)
ANO=$(echo $ANOFIN)
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

EVENT=$(echo "Final de $IN_EVENT". Iniciado el $INICIO. Han sido $DIASTOTAL días en total)

addevent


exit
fi




if [ "$1" = "ip" ]  
then
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"

echo "Añade un contexto, proyecto o nota, que se añadirá en todas las fechas a importar: " ; read NOTA

add_contexto_proyecto

while read LINEA; do
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
     
EVENT=$(echo "$(echo $LINEA | cut -d" " -f2-) "$NOTA" "$ADDTAG" "$ADDCON"")

    
#date -d "$(echo $(date  +'%Y')-$(echo $LINEA | cut -d" " -f1))" +'%Y-%m-%d'    

ANO=$(echo $(date  +'%Y'))
MES=$(echo $LINEA | cut -d"-" -f1)
DIA=$(echo $LINEA | cut -d" " -f1 | cut -d "-" -f2)


CALDIA=$(date -d "$(echo $(date  +'%Y')-$(echo $LINEA | cut -d" " -f1))" +'%Y-%m-%d')

addevent

done < "$2"
exit
fi


if [ "$1" = "i" ]  
then
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"

echo "Añade un contexto, proyecto o nota, que se añadirá en todas las fechas a importar: " ; read NOTA

add_contexto_proyecto

while read LINEA; do
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
     
EVENT=$(echo "$(echo $LINEA | cut -d" " -f2-) "$NOTA" "$ADDTAG" "$ADDCON"")
    
ANO=$(echo $LINEA | cut -d"-" -f1)
MES=$(echo $LINEA | cut -d"-" -f2)
DIA=$(echo $LINEA | cut -d" " -f1 | cut -d "-" -f3)

CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

addevent

done < "$2"
exit
fi




if [ "$1" = "add" ] || [ "$1" = "a" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA      
read -e -p "Mes: " -i "$(date  +'%m')" MES      
read -e -p "Año: " -i "$(date  +'%Y')" ANO      
read -e -p "Hora: " -i "$(date  +'%H:%M')" HORA 
clear
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1)")" = "" ]
then
   NEWCALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d W%W %a')
   echo -e "$(rclone cat "$CAL")\n$(echo "$NEWCALDIA")" | sort | rclone rcat $CAL
   TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
    fi




if [ "$(echo "$TODO" | grep "^$CALDIA")" = "" ]
then
    echo ""
    echo "Esta fecha no está en la plantilla del calendario"
    echo ""
    echo "  Edita fechas pasadas con: c ed"
    echo ""
    exit
fi


if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    echo "Ya hay un evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
    echo ""
    echo -en "Nuevo evento: " ; read -e EVENT
    echo ""
else
    echo ""
    echo -en "Evento: " ; read -e EVENT
fi
echo -en "Quieres añadir un proyecto preestablecido?: " ; read RESPUESTA
if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
then
    TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " +\w" | cut -d"+" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
    echo ""
    echo "Etiquetas ya creadas: "
    echo "$TAGS" |  nl -s '. '
    echo ""
    echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
    echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
    ADDTAG="$(echo +$(echo "$TAGS" | sed -n "$NUM"p))"
fi
#######
echo -en "Quieres añadir un contextos preestablecido?: " ; read RESPUESTA
if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
then
    TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " @\w" | cut -d"@" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
    echo ""
    echo "Contextos ya creadas: "
    echo "$TAGS" |  nl -s '. '
    echo ""
    echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
    echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
    ADDCON="$(echo @$(echo "$TAGS" | sed -n "$NUM"p))"
fi

####
if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    ## Ya hay un evento
    echo ""
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA) → $HORA $EVENT $ADDTAG $ADDCON")
    echo ""
    echo ""
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
else
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $HORA $EVENT $ADDTAG $ADDCON")
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
fi
LOGADD=$(echo "$(date +'%Y/%m/%d %T')  :  ADD EVENT \t $HORA $EVENT $ADDTAG $ADDCON")
echo -ne "$(rclone cat $LOGS)\n$(echo "$LOGADD")" | rclone rcat $LOGS
exit
fi



if [ "$1" = "del" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi    
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA         
read -e -p "Mes: " -i "$(date  +'%m')" MES         
read -e -p "Año: " -i "$(date  +'%Y')" ANO        
clear
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    echo "Hay ya una evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
    echo -en "¿Quieres eliminar este evento?: " ; read RESPUESTA
	    if [ "$RESPUESTA" = "NO" ] || [ "$RESPUESTA" = "N" ] || [ "$RESPUESTA" = "no" ] || [ "$RESPUESTA" = "n" ]
            then
	    echo ""	
            echo "Utiliza el comando app para añadir una tarea"
	    echo ""
            exit
            fi    
fi
clear
TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $EVENT")
echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
echo "Evento eliminado"
LOGADD=$(echo "$(date +'%Y/%m/%d %T')  :  DEL EVENT \t $TASK")
echo -ne "$(rclone cat $LOGS)\n$(echo "$LOGADD")" | rclone rcat $LOGS
exit
fi


if [ "$1" = "deld" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
    fi
TODO="$(rclone cat $CAL_DONE |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA         #  echo $DIA
read -e -p "Mes: " -i "$(date  +'%m')" MES         #  echo $MES
read -e -p "Año: " -i "$(date  +'%Y')" ANO         #  echo $ANO
clear
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    echo "Hay ya una evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
    echo -en "¿Quieres eliminar este evento?: " ; read RESPUESTA
	    if [ "$RESPUESTA" = "NO" ] || [ "$RESPUESTA" = "N" ] || [ "$RESPUESTA" = "no" ] || [ "$RESPUESTA" = "n" ]
            then
	    echo ""	
            echo "Utiliza el comando app para añadir una tarea"
	    echo ""
            exit
            fi    
fi
clear
TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $EVENT")
echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL_DONE
echo "Evento eliminado"
exit
fi

if [ "$1" = "p" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    

CALENDAR_RC=$(rclone cat $CAL |& egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")" | grep -i "$3" | grep -i "$4"| grep -i "$5" )
NOHAYEVENTOS="$(echo "$CALENDAR_RC" |  awk '{print $4}')"
if [ "$NOHAYEVENTOS" = "" ]
then
echo "No hay ningún evento en el Calendario en las próximas 2 semanas"
exit
fi
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)
exit
fi

if [ "$1" = "lsb" ] 
then
rclone cat $CAL | grep -i "$2" | grep -i "$3" | grep -i "$4" | grep -i "$5" 
exit
fi

if [ "$1" = "lsbc" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
rclone cat $CAL | grep -i "$3" | grep -i "$4" | grep -i "$5"
exit
fi

if [ "$1" = "lsmd" ]
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
CALENDAR_RC=$(rclone cat $CAL |& grep "W" | grep -i "$3" | grep -i "$4" | sed 's|http.[^ \t]*|[&](&)|' )
clear
echo ""
echo "# Calendario $2"
echo ""
while read LINEA; do
    echo "## $(date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y')"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/^/- /' | sed 's/\\n/ - /'
    echo " "
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n  | cut -d ":" -f1)
exit
fi

if [ "$1" = "calendar" ]
then
    echo "Calendarios"
    echo "--------------------------"
ls ~/.config/rccalendar/*.conf |   sed 's/.*\///'  | cut -d "." -f1
exit
fi

if [ "$1" = "termux-install" ]
then
pkg upgrade    
pkg install jq termux-api termux-services rclone
mkdir -p ~/.shortcuts
echo "bash ~/.config/rccalendar/c termux" > ~/.shortcuts/Calendario
exit
fi

if [ "$1" = "termux" ]
then
    MENU=$(termux-dialog  sheet -v "Añadir,Borrar,Eventos" | jq '.text' -r)
fi
if [ "$MENU" = "Eventos" ]
then
    if [ "$2" != "" ]
    then
	if [ -f  ~/.config/rccalendar/$2.conf ];
	then
	    echo ""
	else
	    echo "No existe este calendario"
	    exit
	fi
	source ~/.config/rccalendar/$2.conf
        bash ~/.config/rccalendar/c p "$2" | termux-toast -c white -b black
	exit
    fi    
    bash ~/.config/rccalendar/c  | termux-toast -c white -b black
    exit
fi
if [ "$MENU" = "Borrar" ]
then
    if [ "$2" != "" ]
    then
	if [ -f  ~/.config/rccalendar/$2.conf ];
	then
	    echo ""
	else
	    echo "No existe este calendario"
	    exit
	fi
	source ~/.config/rccalendar/$2.conf
    fi
    TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
    CALDIA="$(termux-dialog date -t "Introduce la Fecha"  -d "Y-MM-dd"   | jq '.text' -r)"
    if [ "$CALDIA" = "" ]
    then
	echo ""
	exit
    fi
    clear
    if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
    then
	echo "Hay ya una evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
	RESPUESTA=$(termux-dialog  radio -v "SI,NO" -t "$(echo "Hay ya una evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") ")¿Quieres eliminar este evento?: " | jq '.text' -r)
	if [ "$RESPUESTA" = "NO" ] || [ "$RESPUESTA" = "N" ] || [ "$RESPUESTA" = "no" ] || [ "$RESPUESTA" = "n" ]
	then
	    echo ""
	    echo "Utiliza el comando app para añadir una tarea"
	    echo ""
	    exit
	fi
    fi
    clear
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $EVENT")
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    echo "Evento eliminado"
    exit
fi
if [ "$MENU" = "Añadir" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
clear
FECHA="$(termux-dialog date -t "Introduce la Fecha"  -d "Y-MM-dd"   | jq '.text' -r)"
if [ "$FECHA" = "" ]
then
    echo ""
    exit
    fi
if [ "$(echo "$(echo "$TODO" | grep $FECHA | cut -d " " -f4-)")" != "" ]
then
    echo "Ya hay un evento ese día: $(echo "$(echo "$TODO" | grep $FECHA | cut -d " " -f4-)") "
    echo ""
EVENT="$(termux-dialog -t "Añadir Evento: " | jq '.text' -r)"
if [ "$EVENT" = "" ]
then
    echo ""
    exit
    fi
    echo ""
    echo ""
            else
		echo ""
EVENT="$(termux-dialog -t "Nuevo Evento: " | jq '.text' -r)"
if [ "$EVENT" = "" ]
then
    echo ""
    exit
    fi
		
      fi     
RESPUESTA=$(termux-dialog  radio -v "SI,NO" -t "Quieres añadir una de las etiquetes preestablecidas?: " | jq '.text' -r)
echo $RESPUESTA
    if [ "$RESPUESTA" = "SI" ] 
            then
TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " +\w" | cut -d"+" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
ADDTAG=$(echo "+$(termux-dialog  radio -v "$(echo $TAGS | sed s'| |,|'g)" -t "Selecciona una etiqueta: " | jq '.text' -r)")
fi
RESPUESTA=$(termux-dialog  radio -v "SI,NO" -t "Quieres guardar la geolocalización?: " | jq '.text' -r)
if [ "$RESPUESTA" = "SI" ] 
then    
ADDGEO=$(echo "https://maps.google.com/maps?q="$(termux-location | jq '.latitude' -r)","$(termux-location | jq '.longitude' -r)"")
if [ "$ADDGEO" = "" ]
then
    echo ""
    termux-toast -c white -b black "No funciona la Geolocalizacion. Vuelve a introducir el evento sin ella"
    exit
    fi
fi
if [ "$(echo "$(echo "$TODO" | grep $FECHA | cut -d " " -f4-)")" != "" ]
then
    ## Ya hay un evento
echo ""
                TASK=$(echo "$TODO" | grep -n $FECHA | cut -d ":" -f1)
                RESPUESTA=$(echo "$(echo "$TODO" | grep $FECHA) → $HORA $EVENT $ADDTAG $ADDGEO")
                # Numerar las variables filtradas. La palabra a filtrar con grep tiene que ir entre comillas
                echo ""
                echo ""
                # Añadir el nº de tarea
                # Subir a la nube
                echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
                    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
                    echo "----------------------------"
                    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
                    echo ""
               echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /' | termux-toast -c white -b black                 
else
clear
if [ "$FECHA" = "" ]
then
    echo ""
    exit
    fi
TASK=$(echo "$TODO" | grep -n $FECHA | cut -d ":" -f1)
RESPUESTA=$(echo "$(echo "$TODO" | grep $FECHA | cut -d " " -f1,2,3) $HORA $EVENT $ADDTAG $ADDGEO")
echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|\||\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /' | termux-toast -c white -b black                 
fi
exit
fi


if [ "$1" = "atermux" ] 
then
if [ "$2" != "" ]
then
    if [ -f  ~/.config/rccalendar/$2.conf ];
    then
	echo ""
	else
	echo "No existe este calendario"
	exit
	fi
    source ~/.config/rccalendar/$2.conf
fi    
TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
read -e -p "Día: " -i "$(date  +'%d')" DIA      
read -e -p "Mes: " -i "$(date  +'%m')" MES      
read -e -p "Año: " -i "$(date  +'%Y')" ANO      
read -e -p "Hora: " -i "$(date  +'%H:%M')" HORA 
clear
CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')

if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1)")" = "" ]
then
   NEWCALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d W%W %a')
   echo -e "$(rclone cat "$CAL")\n$(echo "$NEWCALDIA")" | sort | rclone rcat $CAL
   TODO="$(rclone cat $CAL |  sed '/^ *$/d')"
    fi




if [ "$(echo "$TODO" | grep "^$CALDIA")" = "" ]
then
    echo ""
    echo "Esta fecha no está en la plantilla del calendario"
    echo ""
    echo "  Edita fechas pasadas con: c ed"
    echo ""
    exit
fi


if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    echo "Ya hay un evento ese día: $(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)") "
    echo ""
    echo -en "Nuevo evento: " ; read -e EVENT
    echo ""
else
    echo ""
    echo -en "Evento: " ; read -e EVENT
fi
echo -en "Quieres añadir un proyecto preestablecido?: " ; read RESPUESTA
if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
then
    TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " +\w" | cut -d"+" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
    echo ""
    echo "Etiquetas ya creadas: "
    echo "$TAGS" |  nl -s '. '
    echo ""
    echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
    echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
    ADDTAG="$(echo +$(echo "$TAGS" | sed -n "$NUM"p))"
fi
#######
echo -en "Quieres añadir un contextos preestablecido?: " ; read RESPUESTA
if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "s" ]
then
    TAGS=$(echo "$(rclone cat $CAL)\n$(rclone cat $CAL_DONE)" | grep " @\w" | cut -d"@" -f2 | cut -d" " -f1 | awk '!($0 in a) {a[$0];print}' | grep .)
    echo ""
    echo "Contextos ya creadas: "
    echo "$TAGS" |  nl -s '. '
    echo ""
    echo -en "Selecciona el nº de etiqueta: " ; read -e NUM
    echo     "    Etiqueta +"$(echo "$TAGS" | sed -n "$NUM"p)""
    ADDCON="$(echo @$(echo "$TAGS" | sed -n "$NUM"p))"
fi


echo -en "¿Quieres guardar la geolocalización?: " ; read RESPUESTA
if [ "$RESPUESTA" = "SI" ] || [ "$RESPUESTA" = "s" ] || [ "$RESPUESTA" = "si" ] || [ "$RESPUESTA" = "y" ] || [ "$RESPUESTA" = "S" ] || [ "$RESPUESTA" = "Y" ]
then    
ADDGEO=$(echo "https://maps.google.com/maps?q="$(termux-location | jq '.latitude' -r)","$(termux-location | jq '.longitude' -r)"")
if [ "$ADDGEO" = "" ]
then
    echo "No funciona la Geolocalizacion. Vuelve a introducir el evento sin ella"
    exit
    fi
fi



####
if [ "$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f4-)")" != "" ]
then
    ## Ya hay un evento
    echo ""
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA) → $HORA $EVENT $ADDTAG $ADDCON" "$ADDGEO")
    echo ""
    echo ""
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed s'|→|\n|'g | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
else
    clear
    CALDIA=$(date -d "$(echo "$ANO-$MES-$DIA")" +'%Y-%m-%d')
    TASK=$(echo "$TODO" | grep -n $CALDIA | cut -d ":" -f1)
    RESPUESTA=$(echo "$(echo "$TODO" | grep $CALDIA | cut -d " " -f1,2,3) $HORA $EVENT $ADDTAG $ADDCON" "$ADDGEO")
    echo "$TODO" | sed "s|$(echo "$TODO" | sed -n "$TASK"p)|$RESPUESTA|g" | sed '/^ *$/d' | rclone rcat $CAL
    date -d "$(echo "$RESPUESTA " | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$RESPUESTA " | cut -d " " -f4-) | sed 's/→/\n/g'  | sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
fi
LOGADD=$(echo "$(date +'%Y/%m/%d %T')  :  ADD EVENT \t $HORA $EVENT $ADDTAG $ADDCON $ADDGEO")
echo -ne "$(rclone cat $LOGS)\n$(echo "$LOGADD")" | rclone rcat $LOGS
exit
fi



if [ "$1" = "logs" ] || [ "$1" = "log" ]
then
    echo "rccalendar. logs"
    echo "-------------"
rclone cat $LOGS
echo ""
exit
fi


CALENDAR_RC=$(rclone cat $CAL |&  grep -i "$1" | grep -i "$2" | grep -i "$3" |egrep "$(date +"W%V")|$(date --date='+1 week' +"W%V")"  )
NOHAYEVENTOS="$(echo "$CALENDAR_RC" |  awk '{print $4}')"
if [ "$NOHAYEVENTOS" = "" ]
then
echo "No hay ningún evento en el Calendario en las próximas 2 semanas"
exit
fi
echo ""
while read LINEA; do
    date -d "$(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d' ' -f1)" +'%A %d de %B del %Y'
    echo "----------------------------"
    echo -e $(echo "$CALENDAR_RC" | sed -n "$LINEA"p | cut -d " " -f4-) | sed 's/→/\n/g' |sed 's/^ *//g' | sed 's/^/ - /'
    echo ""
done <<< $(echo "$CALENDAR_RC" | cut -d " " -f4- | grep . -n | cut -d ":" -f1)

