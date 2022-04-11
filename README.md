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

