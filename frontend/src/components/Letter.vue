<template>
<!-- Utilisation du v-bind afin de pouvoir choisir le background en fonction de l'état de la case -->
<b-col class="border letter" v-bind:style="{background:letterprop.color}">
    <div class="letter-content">
        {{letterprop.letter}}
    </div>
</b-col>
</template>


<script setup>
import {defineProps} from "vue"

//var dictcolor = {"grey":"#1e1e1e","red":"#cc0808","yellow":"#bd8517"}


// définit des propriétés pour le composant
const letterprop = defineProps({
    letter: {
        type: String,
        default: "",
    },
    color:{
        type: String,
        default: "#1e1e1e",
    },
    animate() {
        var el = document.getElementById('animated');
        el.style.animation = 'none';
        el.offsetHeight; /* trigger reflow */
        el.style.animation = null; 
    }
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
    box-sizing: border-box;

    color:#ffffff;
    animation: flip .75s linear;
    font-size:min(7vh,7vw);
}

.letter:before{
    content: "";
    display: block;
    padding-top: 100%;
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
   to{
     transform: rotateX(180deg);
  }
}
</style>