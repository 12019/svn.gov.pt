﻿using System;
using System.Text;

namespace pt.portugal.eid
{
    public class PTEID_TokenInfo
    {

        private String Label; 
        private String Serial;

        public string label
        {
            get
            {
                return Label;
            }
            private set
            {
                Label = value;
            }
        }

        public string serial
        {
            get
            {
                return Serial;
            }
            private set
            {
                Serial = value;
            }
        }

        internal PTEID_TokenInfo(String label, String serial)
        {
            this.label = label;
            this.serial = serial;
        }
    }
}
