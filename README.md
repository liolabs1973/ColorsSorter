# ColorsSorter
Ce projet est basé sur le projet de fin d'étude d'un étudiant en Electromécanique

L'objectif est de disposer d'un produit réalisé à l'aide d'un arduino utilisé dans le cadre d'un remplacement d'un Automate Programmable Industriel (API)

Le code de ce projet, permet le pilotage d'une chaine de tri de blocs de constructions de type "Plus-Plus" (brique en plastique colorée de la forme d'un piece de puzzel).

Le principe est "simple" d'explication mais particulierment complexe à mettre en oeuvre :
La chaine de tri est composée de différents module, une trémie qui accueillera les briques de construction, un module de séparation veille à recueillir un module à la fois pour l'acheminer (via un tapis roulant dans un 1er temps) vers une chambre d'analyse (munie d'un capteur de couleur), la chambre d'analyse effectue un etude colorimétrique et la compare à sa Base de données de couleur. une fois la couleur analysée, un convoyeur est orienté vers la cellule de stockage correspondante et la brique est alors ménée vers le convoyeur qui fera glisser la module dans la cellule de stockage adéquate.

