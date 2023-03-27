﻿using System.Numerics;

using EmoteScriptLib.Entity.Enum;

namespace EmoteScriptLib.Emotes
{
    public class Move: Emote
    {
        public Move() : base(EmoteType.Move)
        {

        }
        
        public Move(Vector3 origin, Quaternion? orientation = null, float? extent = null)

            : base(EmoteType.Move)
        {
            if (orientation == null)
                orientation = Quaternion.Identity;

            SetOrigin(origin);
            SetOrientation(orientation);

            Extent = extent;
        }
    }
}
