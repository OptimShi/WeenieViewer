﻿using EmoteScriptLib.Entity.Enum;

namespace EmoteScriptLib.Emotes
{
    public class Give : Emote
    {
        public Give()
            
            : base(EmoteType.Give)
        {

        }

        public Give(uint wcid, int stackSize = 1, PaletteTemplate palette = PaletteTemplate.Undef, float shade = 0)

            : base(EmoteType.Give)
        {
            WeenieClassId = wcid;
            StackSize = stackSize;
            Palette = palette;
            Shade = shade;
        }
    }
}
