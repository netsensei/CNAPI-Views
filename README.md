De Cultuurnet API Views module integreert de CNAPI met de Views module waardoor Drupal ontwikkelaars en site bouwers zelf makkelijk lijstjes kunnen maken.

De CultuurNet API is een REST API die de data over events, producties en locaties open stelt voor andere ontwikkelaars.

## Wat heb je nodig?

Een werkende Drupal 7 installatie met deze modules:

* De [cnapi module](https://github.com/davyvandenbremt/cnapi)
* De [views module](http://drupal.org/project/views)

## Hoe gebruik je deze module?

Om een nieuwe pagina te maken die evenementen oplijst, doe je het volgende:

* Ga naar *structure* > *views*
* Klik op *Add a new view*
* Geef je nieuwe view de naam "Evenementen" in *view name*
* Onder description: Show *CNAPI events* in plaats van Show *Content*
* *Create a page* aanvinken. Geef je view een *page title* "events" en een *path* "events"
* Klik op *Save en exit*
* Drupal sluit het venster en navigeert automatisch naar http://jouwsiteurl/events waar je een lijstje van evenementen krijgt te zien.

Om een filter toe te voegen doe je dit:

* Ga naar *structure* > *views*
* Klik op *edit* naast de view "Evenementen*
* Bij *Filter criteria* (linksonder) klik je op de *add* knop
* Check de box naast *Cnapi events: headings* om de CNAPI Headings API filter toe te passen
* Klik op *add and configure filter criteria*
* Kies bij *headings* voor "Concert" (je kan er meerdere tegelijk selecteren)
* Klik op *Apply (all displays)*
* Klik op de *Save* knop (rechtsboven)
* Navigeer nu naar http://jouwsiteurl/events. De lijst wordt nu gefilterd op "Concert"

## Opmerkingen

* Hoewel je dezelfde filter (bv. Query) meerdere keren kan toevoegen, wordt die slechts eenmaal gebruikt.
* Wanneer je een CNAPI View aanmaaknt, dan hoort bij *Format* > *Show* de juiste CNAPI Style plugin aan te staan. CNAPI Events > CNAPI Event, CNAPI Productions > CNAPI Production, CNAPI Actors > CNAPI Actor.

## Credits

Deze module werd gesponsord door [Krimson Drupal Architects](http://krimson.be)