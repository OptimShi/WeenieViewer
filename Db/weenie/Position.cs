using System;
using System.Collections.Generic;
using System.Data.Entity.Core.Common.CommandTrees.ExpressionBuilder;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace WeenieViewer.Db.weenie
{
    public class Position
    {
        public int positionType;
        public uint objCellId;
        public float x;
        public float y;
        public float z;
        public float qw;
        public float qx;
        public float qy;
        public float qz;
    }

    /// <summary>
    ///  Thanks to ACE for these!
    /// </summary>
    public static class PositionExtensions
    {
        public static readonly int BlockLength = 192;
        public static readonly int CellSide = 8;
        public static readonly int CellLength = 24;

        public static Vector3 ToGlobal(this Position p, bool skipIndoors = false)
        {
            // TODO: Is this necessary? It seemed to be loading rogue physics landblocks. Commented out 2019-04 Mag-nus
            //var landblock = LScape.get_landblock(p.LandblockId.Raw);

            // TODO: investigate dungeons that are below actual traversable overworld terrain
            // ex., 010AFFFF
            //if (landblock.IsDungeon)

            byte LandblockX = (byte)((p.objCellId >> 24) & 0xFF);

            byte LandblockY = (byte)((p.objCellId >> 16) & 0xFF);

            var x = LandblockX * BlockLength + p.x;
            var y = LandblockY * BlockLength + p.y;
            var z = p.z;

            return new Vector3(x, y, z);
        }

        public static Vector2? GetMapCoords(this Position pos)
        {
            // no map coords available for dungeons / indoors?
            /*
            if ((pos.objCellId & 0xFFFF) >= 0x100)
                return null;
            */
            var globalPos = pos.ToGlobal();

            // 1 landblock = 192 meters
            // 1 landblock = 0.8 map units

            // 1 map unit = 1.25 landblocks
            // 1 map unit = 240 meters

            var mapCoords = new Vector2(globalPos.X / 240, globalPos.Y / 240);

            // dereth is 204 map units across, -102 to +102
            mapCoords -= Vector2.One * 102;

            return mapCoords;
        }

        public static string GetMapCoordStr(this Position pos)
        {
            var mapCoords = pos.GetMapCoords();

            if (mapCoords == null)
                return null;

            var northSouth = mapCoords.Value.Y >= 0 ? "N" : "S";
            var eastWest = mapCoords.Value.X >= 0 ? "E" : "W";

            return string.Format("{0:0.0}", Math.Abs(mapCoords.Value.Y) - 0.05f) + northSouth + ", "
                 + string.Format("{0:0.0}", Math.Abs(mapCoords.Value.X) - 0.05f) + eastWest;
        }

        public static float Distance2D(Position p1, Position p2)
        {
            // originally this returned the offset instead of distance...
            if (p1.objCellId == p2.objCellId)
            {
                var dx = p2.x- p1.x;
                var dy = p2.y - p1.y;
                return (float)Math.Sqrt(dx * dx + dy * dy);
            }
            //if (p.LandblockId.MapScope == MapScope.Outdoors && this.LandblockId.MapScope == MapScope.Outdoors)
            else
            {
                byte p1_LandblockX = (byte)((p1.objCellId >> 24) & 0xFF);
                byte p1_LandblockY = (byte)((p1.objCellId >> 16) & 0xFF);
                byte p2_LandblockX = (byte)((p2.objCellId >> 24) & 0xFF);
                byte p2_LandblockY = (byte)((p2.objCellId >> 16) & 0xFF);

                // verify this is working correctly if one of these is indoors
                var dx = (p2_LandblockX - p1_LandblockX) * 192 + p2.x - p1.x;
                var dy = (p2_LandblockY - p1_LandblockY) * 192 + p2.y - p1.y;
                return (float)Math.Sqrt(dx * dx + dy * dy);
            }
        }


    }
}
