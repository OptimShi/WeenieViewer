﻿using System.Numerics;

using EmoteScriptLib.Entity.Enum;

namespace EmoteScriptLib.Emotes
{
    public class Turn : Emote
    {
        public Turn()
            
            : base(EmoteType.Turn)
        {

        }
        
        public Turn(Quaternion angle)

            : base(EmoteType.Turn)
        {
            SetOrientation(angle);
        }
    }
}
