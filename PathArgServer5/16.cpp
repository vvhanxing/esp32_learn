
static void main(String[] args)
{
    byte[] org = {1, 2, 3, 15, 10, 16, 17, 32, 0, 8};
    String hexstr = DataConvertUtil.byteArraytoHexString(org);
    System.out.println("转化结果：" + hexstr);
}

public
static String byteArraytoHexString(byte[] b)
{
    int iLen = b.length;
    StringBuffer sb = new StringBuffer(iLen * 2);
    for (int i = 0; i < iLen; i++)
    {
        int intTmp = b[i];
        while (intTmp < 0)
        {
            intTmp = intTmp + 256;
        }
        if (intTmp < 16)
        {
            sb.append("0");
        }
        sb.append(Integer.toString(intTmp, 16));
    }
    return sb.toString().toUpperCase();
}