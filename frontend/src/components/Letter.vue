<template>
<!-- Utilisation du v-bind afin de pouvoir choisir le background en fonction de l'état de la case -->
<b-col class="border" v-bind:style="{background:color}" style="max-width:75px; height:75px; color:#ffffff">
    {{letter}}
</b-col>
</template>


<script setup>
import {defineProps} from "vue"

//var dictcolor = {"grey":"#1e1e1e","red":"#cc0808","yellow":"#bd8517"}


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


console.log(letterprop.letter); // to avoid unused variable warning

</script>
