<template>
<!-- Utilisation du v-bind afin de pouvoir choisir le background en fonction de l'état de la case -->
<b-col class="border" v-bind:style="{background:letterprop.color}" style="max-width:75px; height:75px; color:#ffffff">
    {{letterprop.letter}}
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
    })



</script>
