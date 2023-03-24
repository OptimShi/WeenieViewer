﻿using EmoteScriptLib.Entity.Enum;

namespace EmoteScriptLib.Emotes
{
    public class UntrainSkill : Emote
    {
        public UntrainSkill() : base(EmoteType.UntrainSkill)
        {

        }
        
        public UntrainSkill(Skill skill)

            : base(EmoteType.UntrainSkill)
        {
            Stat = (int)skill;
        }
    }
}
