﻿using System;
using System.Collections.Generic;
using System.Text;
using datatool;

namespace Maptool
{
    class ZoneTool : Tool
    {
        private List<EntityType> types;

        public ZoneTool()
        {
            types = new List<EntityType>();
            types.Add(new ZoneEntityType());
        }


        public override Entity createEntity()
        {
            return new ZoneEntity();
        }

        public override bool isThisOurs(Entity ent)
        {
            return (ent is ZoneEntity);
        }

        public override bool isAreaBased()
        {
            return true;
        }

        public override List<EntityType> getTypes()
        {
            return types;
        }

        public override string saveConfig(Entity ent)
        {
            string o = "";
            ZoneEntity z = (ZoneEntity)ent;

            o += "zone {";
            o += "  width = " + z.Width;
            o += "  height = " + z.Height;
            o += "  x = " + z.X;
            o += "  y = " + z.Y;
            o += "  angle = " + z.Angle;
            o += "}";

            return o;
        }

        public override Entity loadConfig(ConfuseSection sect)
        {
            ZoneEntity ent = new ZoneEntity();
            ent.Type = types[0];

            ent.Width = sect.get_int("width", 20);
            ent.Height = sect.get_int("height", 20);
            ent.X = sect.get_int("x", 0);
            ent.Y = sect.get_int("y", 0);
            ent.Angle = sect.get_int("angle", 0);

            return ent;
        }
    }
}
