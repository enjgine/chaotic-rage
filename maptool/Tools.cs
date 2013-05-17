﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Maptool
{
    static class Tools
    {
        public static ZoneTool Zone;
        public static LightTool Light;


        /**
         * Loads tool classes
         **/
        public static void Init()
        {
            Tools.Zone = new ZoneTool();
            Tools.Light = new LightTool();
        }
    }
}
