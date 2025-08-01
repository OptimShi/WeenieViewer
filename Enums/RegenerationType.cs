using System;

namespace WeenieViewer.Enums
{
    [Flags]
    public enum RegenerationType : uint
    {
        Undef = 0x0,
        Destruction = 0x1,
        PickUp = 0x2,
        Death = 0x4
    }
}