<template>
<!-- Utilisation du v-bind afin de pouvoir choisir le background en fonction de l'état de la case -->
    <b-col ref="lettre" class="border letter" :class="{'letter-animate':animate, 'letter-content-animate':animate & animateContent, 'letter-very-small':letterprop.size >= 8, 'letter-small':letterprop.size > 6 && letterprop.size < 8, 'letter-big':letterprop.size <= 6}" v-bind:style="{background:letterprop.color}">
        <div class="letter-content">
            {{letterprop.letter}}
        </div>
    </b-col>
</template>


<script setup>
import {defineProps, onBeforeMount, ref, watch} from "vue"

//var dictcolor = {"grey":"#1e1e1e","red":"#cc0808","yellow":"#bd8517"}
let lettre = ref(null)
let animate = ref(false)
let animateContent = ref(true)

// définit des propriétés pour le composant
const letterprop = defineProps({
    letter: {
        type: String,
        default: "",
    },
    size: {
        type: Number,
        default: 5,
    },
    color:{
        type: String,
        default: "#1e1e1e",
    },
    animate:{
        type: Boolean,
        default: true,
    }
})

onBeforeMount(() => {
    animate.value = letterprop.animate
})

// watch( () => letterprop.color, function (newVal) {
watch( () => letterprop.color, function () {
    if (lettre.value == null) { return }
    if (!letterprop.animate) { return }
    animateContent.value = false;

    lettre.value.$el.style.animation = 'none';
    lettre.value.$el.offsetHeight; /* trigger reflow */
    lettre.value.$el.style.animation = null; 

    // if (newVal=="#cc0808") {
        // // console.log("masterclass");
        // var masterclass = new Audio("audio/masterclass.mp3") 
        // <audio autoplay>
        //     <source src="audio/masterclass.mp3" />
        // </audio>
    // }
})

watch( () => letterprop.letter, function () {
    if (lettre.value == null) { return }
    if (!letterprop.animate || !animateContent.value) { return }

    animate.value = false
    
    lettre.value.$el.style.animation = 'none';
    lettre.value.$el.offsetHeight; /* trigger reflow */
    lettre.value.$el.style.animation = null; 

    animate.value = true
    
})


</script>

<style scoped>
.letter {
    display:flex;
    flex-wrap: wrap;
    max-width: min(8vw, 8vh);
    max-height: min(8vw, 8vh);
    width:500px;
    height:500px;
    position: relative;
    flex-basis: calc(10%);
    border-radius: 1px !important;
    border-color: #2e2e2e !important;
    border-style: inset;
    box-sizing: border-box;

    font-size:min(6vh,6vw);
    color:#ffffff;
}
.letter-very-small {
    max-width: min(5vw, 5vh);
    max-height: min(5vw, 5vh);
    font-size:min(4vh,4vw);
}

.letter-small {
    max-width: min(7w, 7vh);
    max-height: min(7vw, 7vh);
    font-size:min(5vh,5vw);
}

.letter-big {
    max-width: min(9vw, 9vh);
    max-height: min(9vw, 9vh);
    font-size:min(7vh,7vw);
}

.letter-animate {
    animation: flip .75s linear;
    animation-timing-function:ease-in-out;
    animation-fill-mode:backwards;

    transition-property: background-color;
    transition-duration: .5s;
}

.letter-content-animate {
    animation: zoom .5s linear;
    animation-timing-function:ease-in-out;
    animation-fill-mode:forwards;
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
    transform: rotateX(0deg);
}
   50% {
     transform: rotateX(90deg);
  }
  100% {
      transform:rotateX(0deg);
  }
}


@keyframes zoom {
  0% {
    transform: scale(1, 1);
  }
  50% {
    transform: scale(1.2, 1.2);
  }
  100% {
    transform: scale(1, 1);
  }
}
</style>