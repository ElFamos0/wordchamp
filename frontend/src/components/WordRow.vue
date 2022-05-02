<script setup>
import WordLetter from '@/components/WordLetter.vue';
import {defineProps, ref, watch} from "vue"

// la méthode de construire en fonction de la taille de la solution me semble vraiment pas opti cela induit une sorte de ralentissement chiant
const rowprop = defineProps({
    solution: String,
    word: String,
    colors: Array,
    submitted: Boolean,
    size:Number,
    animate: {
      type: Boolean,
      default: true
    },
})

// storage de la couleur de chacune des lignes

let b = new Array(rowprop.solution.length);
const colortab = ref(b);

/*
Ceci est un watcher il va permettre de surveiller les changements d'une variable et d'appeler une fonction lorsqu'elle change

En particulier ici on vérifie si la ligne est "validée" par l'utilisateur et peut être traité par l'algorithme

Ici le traitement se fait en frontend mais il faudrait peut être faire un traitement en backend
*/
const grey = "#4a4a4a";
const red = "#cc0808";
const yellow = "#bd8517";

async function Update(newVal)  {
        if (newVal) {
            let colors = [grey,yellow,red]
            for (let i = 0; i < rowprop.colors.length; i++) {
                colortab.value[i] = colors[rowprop.colors[i]];

                if (rowprop.animate) {
                    await new Promise(resolve => setTimeout(resolve, 400));
                }
            }
        }
}

watch( () => rowprop.submitted, Update);

if(rowprop.submitted) {
    Update(rowprop.submitted)
}

</script>

<template>
    <b-container>
        <b-row class="justify-content-center ligne">
            <WordLetter v-for="i in rowprop.size" :animate="rowprop.animate" :key="i" :size="rowprop.size" :letter=word[i-1] :color=colortab[i-1]></WordLetter>
        </b-row>
    </b-container>
</template>


<style scoped>
.ligne {
    /* margin-bottom:12px; */
}
.bg {
    background-color: #1e1e1e;
}
</style>