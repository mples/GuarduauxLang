//
// Created by mateusz on 04.06.18.
//

#ifndef GUARDUAUX_LANG_GRAPHICOBJECT_H
#define GUARDUAUX_LANG_GRAPHICOBJECT_H

namespace Guarduaux{
    class GraphicObject {
    public:
        virtual ~GraphicObject() = default;

        virtual void draw() = 0;
    };
}


#endif //GUARDUAUX_LANG_GRAPHICOBJECT_H
