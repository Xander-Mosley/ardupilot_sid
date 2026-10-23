#!/usr/bin/env python3
"""Editable C4 diagram source. Render with Python + matplotlib; output SVG/PNG."""
from pathlib import Path
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch

ROOT=Path(__file__).parent

def diagram(name,title,nodes,edges,boundaries=()):
    fig,ax=plt.subplots(figsize=(16,10));ax.set_xlim(0,16);ax.set_ylim(0,10);ax.axis('off')
    ax.set_title(title,fontsize=18,pad=15)
    for x,y,w,h,label in boundaries:
        ax.add_patch(FancyBboxPatch((x,y),w,h,boxstyle='round,pad=0.1',fill=False,linestyle='--',edgecolor='#64748b'))
        ax.text(x+.1,y+h-.25,label,fontsize=10,color='#475569')
    for key,(x,y,label,kind) in nodes.items():
        color={'Person':'#334155','External system':'#64748b','Software system':'#155e75','Container':'#0369a1','Component':'#2563eb'}[kind]
        ax.add_patch(FancyBboxPatch((x-1.65,y-.55),3.3,1.1,boxstyle='round,pad=0.08',facecolor=color,edgecolor='white'))
        ax.text(x,y,f'{label}\n[{kind}]',ha='center',va='center',color='white',fontsize=10)
    for src,dst,label in edges:
        x,y,*_=nodes[src];xx,yy,*_=nodes[dst]
        dx,dy=xx-x,yy-y
        fraction=min(1.75/abs(dx) if dx else float('inf'),.65/abs(dy) if dy else float('inf'))
        ax.annotate('',xy=(xx-fraction*dx,yy-fraction*dy),xytext=(x+fraction*dx,y+fraction*dy),arrowprops=dict(arrowstyle='->',color='#475569',connectionstyle='arc3,rad=0.02'))
        ax.text((x+xx)/2,(y+yy)/2+.12,label,fontsize=8,ha='center',va='center',bbox=dict(facecolor='white',edgecolor='none',alpha=.85))
    ax.text(.2,.1,'Read arrows as directed interactions. Dashed borders show ownership. SITL is the only execution target tested.',fontsize=9)
    fig.tight_layout();fig.savefig(ROOT/(name+'.svg'));fig.savefig(ROOT/(name+'.png'),dpi=150);plt.close(fig)

def main():
    diagram('c4_context','C4 Level 1 — System context',{
        'user':(2,8,'Experiment operator','Person'),
        'ros':(7,8,'ros2_sid\nSelect and execute mission','Software system'),
        'ap':(7,3,'ArduPlane\nGUIDED + excitation safeguards','Software system'),
        'sim':(13,3,'Simulated aircraft\nActuator and flight dynamics','External system'),
        'analysis':(13,8,'Validation and plots','Software system')},[
        ('user','ros','Select / start / stop'),('ros','ap','DDS excitation; clock/status return'),
        ('ap','sim','PWM → dynamics; sensors return'),('ap','analysis','DataFlash'),('ros','analysis','Publisher records'),('analysis','user','Evidence / pass-fail')])
    diagram('c4_containers','C4 Level 2 — Execution and evidence',{
        'user':(2,8,'Operator / simulated RC gate','Person'),
        'mission':(7,8,'run_mission_SITL.py or HITL.py\nPython / rclpy','Container'),
        'agent':(7,5,'Micro XRCE-DDS Agent\nROS DDS ↔ XRCE UDP','Container'),
        'ap':(7,2,'ArduPlane SITL firmware\nC++ flight loop','Container'),
        'sim':(13,2,'Plane simulator\nBuilt-in SITL model','Container'),
        'plots':(13,8,'ROS bag → surface_analysis\nCSV + PNG/PDF + report','Container')},[
        ('user','mission','Console or fresh RC switch'),('mission','agent','/ap/sid/control_surface'),
        ('agent','ap','UDP 2021; domain 0'),('ap','mission','/ap/time; /ap/sid/status'),
        ('ap','sim','Actuator output / sensor feedback'),('ap','plots','DDS output → rosbag2; DataFlash cross-check'),('mission','plots','Sequence-stamped command CSV')])
    diagram('c4_components','C4 Level 3 — ArduPlane additive output path',{
        'dds':(2,8,'AP_DDS subscriber\nDeserialize sample','Component'),
        'ext':(7,8,'AP_ExternalControl_Plane\nBounded mailbox','Component'),
        'engine':(12,8,'PlaneSurfaceExcitation\nValidate / gate / limit / ramp','Component'),
        'baseline':(2,4,'GUIDED + stabilization\nBaseline logical commands','Component'),
        'mix':(7,4,'Existing surface mixers\nBaseline + separate delta mixing','Component'),
        'servo':(12,4,'SRV_Channel::calc_pwm\nCalibration, add, clamp, guards','Component'),
        'log':(7,1,'DataFlash + DDS output/status\nROS bag → offline plots','Component')},[
        ('dds','ext','Typed command'),('ext','engine','Latest sample + disable edge'),('engine','mix','Normalized axis perturbation'),
        ('baseline','mix','Normal outputs continue'),('mix','servo','Per-surface baseline and delta'),
        ('servo','log','PWM / clipping; state / sequence / timestamps')],[(.2,.4,15.4,8.6,'ArduPlane firmware boundary')])

if __name__=='__main__':main()
