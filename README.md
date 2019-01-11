# TMA_RICM5

# SPEC ENCODAGE

* La taille est codé sur 4 octets
* Le nom est caché ensuite sur un nombre inconnu d'octet
* On insère 3 octets NUL pour séparer le nom et le flux
* Le flux est encodé sur le reste du fichier


! Prendre en compte le cas où le jpeg ne rentre pas dans l'image 