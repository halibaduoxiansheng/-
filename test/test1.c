const uint8Array = new Uint8Array([
    170, 85, 0, 1, 1, 0, 101, 0, 
    49, 50, 51, 52, 53, 54, 55, 56, 
    0, 73, 67, 77, 95, 48, 48, 49, 
    0, 0, 48, 46, 48, 46, 49, 0, 
    0, 0, 56, 52, 97, 53, 54, 100, 
    118, 49, 46, 48, 54, 56, 48, 55, 
    57, 100, 53, 51, 99, 101, 52, 57, 
    56, 53, 48, 98, 48, 100, 51, 98, 
    56, 56, 57, 51, 99, 100, 101, 48, 
    99, 101, 55, 52, 99, 49, 50, 51, 
    52, 53, 54, 55, 56, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 10
]);

// 检查头部
const head = (uint8Array[0] << 8) | uint8Array[1];
if (head !== 0x55aa) {
    console.error('Invalid head:', head);
} else {
    // 解析其他字段
    const ver = uint8Array[2];
    const seqNo = uint8Array[3];
    const cid = uint8Array[4];
    const reFlag = uint8Array[5];
    const len = (uint8Array[6] << 8) | uint8Array[7];

    // 解析 data 部分
    const dataStartIndex = 8;
    const data = uint8Array.slice(dataStartIndex, dataStartIndex + len);
    
    // 解析 dev_statusinfo
    const vendor = String.fromCharCode(...data.slice(0, 9)).trim();
    const product = String.fromCharCode(...data.slice(9, 18)).trim();
    const version = String.fromCharCode(...data.slice(18, 26)).trim();
    const devid = String.fromCharCode(...data.slice(26, 39)).trim();
    const devname = String.fromCharCode(...data.slice(39, 69)).trim();
    const sn = String.fromCharCode(...data.slice(69, 101)).trim();

    console.log({
        head,
        ver,
        seqNo,
        cid,
        reFlag,
        len,
        dev_statusinfo: {
            vendor,
            product,
            version,
            devid,
            devname,
            sn
        }
    });
}
