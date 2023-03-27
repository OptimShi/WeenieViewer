﻿using EmoteScriptLib.Entity.Enum;

namespace EmoteScriptLib.Emotes
{
    public class InqRawAttributeStat : Emote
    {
        public InqRawAttributeStat() : base(EmoteType.InqRawAttributeStat)
        {
            Init();
        }
        
        public InqRawAttributeStat(PropertyAttribute stat, int min, int max)

            : base(EmoteType.InqRawAttributeStat)
        {
            Init();
            
            Stat = (int)stat;

            Min = min;
            Max = max;
        }

        public void Init()
        {
            AddValidBranches(Branch.TestQuality);
        }
    }
}
