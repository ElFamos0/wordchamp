<template>
<!-- Utilisation du v-bind afin de pouvoir choisir le background en fonction de l'état de la case -->
    <b-col ref="lettre" class="border letter" v-bind:style="{background:letterprop.color}">
        <div class="letter-content">
            {{letterprop.letter}}
        </div>
    </b-col>
</template>


<script setup>
import {defineProps, ref, watch} from "vue"

//var dictcolor = {"grey":"#1e1e1e","red":"#cc0808","yellow":"#bd8517"}
let lettre = ref(null)

// définit des propriétés pour le composant
const letterprop = defineProps({
    letter: {
        type: String,
        default: "",
    },
    color:{
        type: String,
        default: "#1e1e1e",
    }
})

// watch( () => letterprop.color, function (newVal) {
watch( () => letterprop.color, function () {
    if (lettre.value == null) { return}
    lettre.value.$el.style.animation = 'none';
    lettre.value.$el.offsetHeight; /* trigger reflow */
    lettre.value.$el.style.animation = null; 
    // if (newVal=="#cc0808") {
        // console.log("masterclass");
        // var masterclass = new Audio("audio/masterclass.mp3") 
        // <audio autoplay>
        //     <source src="audio/masterclass.mp3" />
        // </audio>
    // }
})



</script>

<style scoped>
.letter {
    display:flex;
    flex-wrap: wrap;
    max-width: min(10vw, 10vh);
    max-height: min(10vw, 10vh);
    width:500px;
    height:500px;
    position: relative;
    flex-basis: calc(10%);
    border: 1px solid;
    border-color: #2f2f2f !important;
    box-sizing: border-box;

    color:#ffffff;
    animation: flip .75s linear;
    animation-timing-function:ease-in-out;
    animation-fill-mode:backwards;
    font-size:min(7vh,7vw);

    transition-property: background-color;
    transition-duration: .5s;
}

.letter:before{
    content: "";
    display: block;
    padding-top: 100%;
}

.letter-content:after{
    animation: flip .75s linear;
}

.letter-content {
  position: absolute;
  top: 0; left: 0;
  height: 100%;
  width: 100%;

  display: flex;               /* added for centered text */
  justify-content: center;     /* added for centered text */
  align-items: center;         /* added for centered text */
}

@keyframes flip{
   from{
    transform: rotateX(180deg);
}
   to{
     transform: rotateX(0deg);
  }
}
</style>