.text
.global reload_segments
#.type reload_segments, @function

reload_segments:
   # Reload CS register containing code selector:
   LJMP   $0x08, $reload_CS # 0x08 points at the new code selector
reload_CS:
   # Reload data segment registers:
   MOV   $0x10, %AX  # 0x10 points at the new data selector
   MOV   %AX, %DS
   MOV   %AX, %ES
   MOV   %AX, %FS
   MOV   %AX, %GS
   MOV   %AX, %SS
   RET
.end
